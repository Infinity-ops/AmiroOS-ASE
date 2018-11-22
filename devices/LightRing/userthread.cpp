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
     this->sleep(MS2ST(1000));


    while (!this->shouldTerminate())
    {
      // LOOP CODE
    
    /*
     * INSERT CUSTOM CODE HERE
     */
     

    //chprintf((BaseSequentialStream*)&global.sercanmux1,"0x%04X \n", &global.i2scfg.i2s_rx_buf);
      for(int i=0; i < 20; i++)
      {

	      chprintf((BaseSequentialStream*) &global.sercanmux1, "i2s_rx_buffer: \n");
          chprintf((BaseSequentialStream*) &global.sercanmux1, "0x%08X\n",
		            global.i2s_rx_buf[i]);
	//      chprintf((BaseSequentialStream*) &global.sercanmux1, "i2s_tx_buffer: \n");
	//      chprintf((BaseSequentialStream*) &global.sercanmux1, "0x%04X \n",
	//                  global.i2s_tx_buf[i]);
          chprintf((BaseSequentialStream*) &global.sercanmux1, "0x%08X \n",
                        global.i2scfg.rx_buffer);
      }
      chprintf((BaseSequentialStream*) &global.sercanmux1, "0x%032X \n",
                    global.i2scfg.rx_buffer);
//      chprintf((BaseSequentialStream*) &global.sercanmux1, "i2s_tx_buffer: \n");
//      chprintf((BaseSequentialStream*) &global.sercanmux1, "0x%04X \n",
//                  global.i2s_tx_buf[3999]);
      


    chprintf((BaseSequentialStream*) &global.sercanmux1,"stop exchange \n");
    chprintf((BaseSequentialStream*) &global.sercanmux1,"checking \n");


  }
  i2sStopExchange(&I2SD2);
  this->sleep(MS2ST(1000));
  
  // SHUTDOWN CODE

  return RDY_OK;
}
