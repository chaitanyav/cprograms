#include <sys/param.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/conf.h>
#include <sys/uio.h>
#include <sys/malloc.h>

#define BUFFER_SIZE 256

static d_open_t echo_open;
static d_close_t echo_close;
static d_read_t echo_read;
static d_write_t echo_write;

static struct cdevsw echo_cdevsw = {
  .d_version = D_VERSION,
  .d_open = echo_open,
  .d_close = echo_close,
  .d_read = echo_read,
  .d_write = echo_write,
  .d_name = "echo"
};

typedef struct echo {
  char buffer[BUFFER_SIZE];
  int length;
} echo_t;

static echo_t *echo_message;
static struct cdev *echo_dev;

static int echo_open(struct cdev *dev, int oflags, int devtype, struct thread *td) {
  uprintf("Opening echo device\n");
  return 0;
}

static int echo_close(struct cdev *dev, int fflag, int devtype, struct thread *td) {
  uprintf("Closing echo device\n");
  return 0;
}

static int echo_write(struct cdev *dev, struct uio *uio, int ioflag) {
  int error = 0;
  error = copyin(uio->uio_iov->iov_base, echo_message->buffer, MIN(uio->uio_iov->iov_len, BUFFER_SIZE - 1));
  if(error != 0) {
    uprintf("Write failed\n");
    return error;
  }

  *(echo_message->buffer + MIN(uio->uio_iov->iov_len, BUFFER_SIZE - 1)) = 0;
  echo_message->length = MIN(uio->uio_iov->iov_len, BUFFER_SIZE - 1);

  return error;
}

static int echo_read(struct cdev *dev, struct uio *uio, int ioflag) {
  int error = 0;
  int amount;

  amount = MIN(uio->uio_resid, (echo_message->length - uio->uio_offset > 0) ? echo_message->length - uio->uio_offset : 0);
  error = uiomove(echo_message->buffer + uio->uio_offset, amount, uio);
  if(error != 0) {
    uprintf("Read failed\n");
  }

  return error;
}

static int echo_modevent(module_t mod __unused, int event, void *arg __unused) {
  int error = 0;
  switch(event) {
    case MOD_LOAD:
      echo_message = malloc(sizeof(echo_t), M_TEMP, M_WAITOK);
      echo_dev = make_dev(&echo_cdevsw, 0, UID_ROOT, GID_WHEEL, 0600, "echo");
      uprintf("Echo driver loaded\n");
      break;
    case MOD_UNLOAD:
      destroy_dev(echo_dev);
      free(echo_message, M_TEMP);
      uprintf("Echo driver unloaded\n");
      break;
    default:
      error = EOPNOTSUPP;
      break;
  }

    return error;
}

DEV_MODULE(echo, echo_modevent, NULL);
