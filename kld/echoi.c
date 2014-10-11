#include <sys/param.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/systm.h>

#include <sys/conf.h>
#include <sys/uio.h>
#include <sys/malloc.h>
#include <sys/ioccom.h>

MALLOC_DEFINE(M_ECHOI, "echoi_buffer", "buffer for the echoi driver");

#define ECHOI_CLEAR_BUFFER _IO('E', 1)
#define ECHOI_SET_BUFFER_SIZE _IOW('E', 2, int)

static d_open_t echoi_open;
static d_close_t echoi_close;
static d_read_t echoi_read;
static d_write_t echoi_write;
static d_ioctl_t echoi_ioctl;

static struct cdevsw echoi_cdevsw = {
  .d_version = D_VERSION,
  .d_open = echoi_open,
  .d_close = echoi_close,
  .d_read = echoi_read,
  .d_write = echoi_write,
  .d_ioctl = echoi_ioctl,
  .d_name = "echoi"
};

typedef struct echoi {
  int buffer_size;
  char *buffer;
  int length;
} echoi_t;

static echoi_t *echoi_message;
static struct cdev *echoi_dev;

static int echoi_open(struct cdev *dev, int oflags, int devtype, struct thread *td) {
  uprintf("Opening echoi device\n");
  return 0;
}

static int echoi_close(struct cdev *dev, int oflags, int devtype, struct thread *td) {
  uprintf("Closing echoi device\n");
  return 0;
}

static int echoi_write(struct cdev *dev, struct uio *uio, int ioflag) {
  int error = 0;
  int amount;

  amount = MIN(uio->uio_resid, (echoi_message->buffer_size - 1 - uio->uio_offset > 0) ? echoi_message->buffer_size - 1 - uio->uio_offset : 0);

  if(amount == 0) {
    return error;
  }

  error = uiomove(echoi_message->buffer, amount, uio);
  if(error != 0) {
    uprintf("Write failed\n");
    return error;
  }

  echoi_message->buffer[amount] = '\0';
  echoi_message->length = amount;

  return error;
}

static int echoi_read(struct cdev *dev, struct uio *uio, int ioflag) {
  int error = 0;
  int amount;

  amount = MIN(uio->uio_resid, (echoi_message->length - uio->uio_offset > 0) ? echoi_message->length - uio->uio_offset : 0);
  error = uiomove(echoi_message->buffer + uio->uio_offset, amount, uio);
  if(error != 0) {
    uprintf("Read failed\n");
  }
  return error;
}

static int echoi_set_buffer_size(int size) {
  int error = 0;
  if(echoi_message->buffer_size == size) {
    return error;
  }

  if(size >= 128 && size <= 512) {
    echoi_message->buffer = realloc(echoi_message->buffer, size, M_ECHOI, M_WAITOK);
    echoi_message->buffer_size = size;
    if(echoi_message->length >= size) {
      echoi_message->length = size - 1;
      echoi_message->buffer[size - 1] = '\0';
    }
  } else {
    error = EINVAL;
  }

  return error;
}

static int echoi_ioctl(struct cdev *dev, u_long cmd, caddr_t data, int fflag, struct thread *td) {
  int error = 0;
  switch(cmd) {
    case ECHOI_CLEAR_BUFFER:
      memset(echoi_message->buffer, '\0', echoi_message->buffer_size);
      echoi_message->length = 0;
      uprintf("Buffer cleared\n");
      break;
    case ECHOI_SET_BUFFER_SIZE:
      error = echoi_set_buffer_size(*(int *)data);
      if(error == 0) {
        uprintf("Buffer resized\n");
      }
      break;
    default:
      error = ENOTTY;
      break;
  }
  return 0;
}

static int echoi_modevent(module_t mod __unused, int event, void *arg __unused) {
  int error = 0;
  switch(event) {
    case MOD_LOAD:
      echoi_message = malloc(sizeof(echoi_t), M_ECHOI, M_WAITOK);
      echoi_message->buffer_size = 256;
      echoi_message->buffer = malloc(echoi_message->buffer_size, M_ECHOI, M_WAITOK);
      echoi_dev = make_dev(&echoi_cdevsw, 0, UID_ROOT, GID_WHEEL, 0600, "echoi");
      uprintf("echoi driver loaded\n");
      break;
    case MOD_UNLOAD:
      destroy_dev(echoi_dev);
      free(echoi_message->buffer, M_ECHOI);
      free(echoi_message, M_ECHOI);
      uprintf("echoi driver unloaded\n");
      break;
    default:
      error = EOPNOTSUPP;
      break;
  }

  return error;
}

DEV_MODULE(echoi, echoi_modevent, NULL);
