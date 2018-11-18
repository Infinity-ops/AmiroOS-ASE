#include "userthread.hpp"
#include <chprintf.h>

#include <hal.h>
#include "global.hpp"

using namespace amiro;

extern Global global;

UserThread::UserThread() :
  chibios_rt::BaseStaticThread<USER_THREAD_STACK_SIZE>()
{
}

UserThread::~UserThread()
{
}

msg_t
UserThread::main()
{
  i2sStart(&I2SD2, &global.i2scfg);
  i2sStartExchange(&I2SD2);
  while (!this->shouldTerminate())
  {
    /*
     * INSERT CUSTOM CODE HERE
     */
    chprintf((BaseSequentialStream*)&global.sercanmux1,"starts exchange \n");
    i2sStopExchange(&I2SD2);
    //chprintf((BaseSequentialStream*)&global.sercanmux1,"0x%04X \n", &global.i2scfg.i2s_rx_buf);
    chprintf((BaseSequentialStream*)&global.sercanmux1, "i2s_rx_buffer: \n");
  //  for(int i=0; i<I2S_BUF_SIZE; i++)
   // {
     //   chprintf((BaseSequentialStream*)&global.sercanmux1, "%d ", &global.i2scfg.rx_buffer[i]);
    //}

    chprintf((BaseSequentialStream*)&global.sercanmux1,"stop exchange \n");
    chprintf((BaseSequentialStream*)&global.sercanmux1,"checking \n");
    this->sleep(MS2ST(1000));



  }

  return RDY_OK;
}
