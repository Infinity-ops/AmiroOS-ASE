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
    // INIT CODE
     i2sInit();
     i2sStart(&I2SD2, &global.i2scfg);
     chprintf((BaseSequentialStream*) &global.sercanmux1,"starts exchange \n");
     i2sStartExchange(&I2SD2);
     this->sleep(MS2ST(10000));
     i2sStopExchange(&I2SD2);
     i2sStop(&I2SD2);


    while (!this->shouldTerminate())
    {
      // LOOP CODE
    
    /*
     * INSERT CUSTOM CODE HERE
     */
     


      for(int i=0; i < 8000; i++)
      {

          chprintf((BaseSequentialStream*) &global.sercanmux1, "%d, %d\n",
                    i, global.i2s_rx_buf[i]);

      }




    chprintf((BaseSequentialStream*) &global.sercanmux1,"stop exchange \n");
    chprintf((BaseSequentialStream*) &global.sercanmux1,"checking \n");

   this->sleep(MS2ST(1000));


  }

  // SHUTDOWN CODE

  return RDY_OK;
}
