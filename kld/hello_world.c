#include <sys/param.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/systm.h>
#include <sys/types.h>

static int hello_world_modevent(module_t mod __unused, int event, void *arg __unused) {
  int error = 0;
  switch(event) {
    case MOD_LOAD:
      uprintf("Hello World Module loaded\n");
      break;
    case MOD_UNLOAD:
      uprintf("Hello World Module unloaded\n");
      break;
    default:
      error = EOPNOTSUPP;
      break;
  }

  return error;
}

static moduledata_t hello_world_mod = {
  "hello_world",
  hello_world_modevent,
  NULL
};

DECLARE_MODULE(hello_world, hello_world_mod, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
