#include "userthread.hpp"
#include <chprintf.h>

#include <hal.h>
#include "global.hpp"
#include <algorithm>

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
    //     this->sleep(MS2ST(10000));
    //     i2sStopExchange(&I2SD2);
    //     i2sStop(&I2SD2);


    while (!this->shouldTerminate())
    {
        // LOOP CODE

        /*
     * INSERT CUSTOM CODE HERE
     */

        // uint32_t samples[I2S_BUF_SIZE];
        std::vector<uint32_t> samples;

        //chprintf((BaseSequentialStream*) &global.sercanmux1, "i1= %d\n",i);
        // int sample = 0;
        for(int i=0; i < I2S_BUF_SIZE ; i++)
        {

            if ((global.i2s_rx_buf[i] != 0) && (global.i2s_rx_buf[i] != -1) )
            {
                // sample = global.i2s_rx_buf[i];
                // samples[i] = global.i2s_rx_buf[i];
                samples.push_back(global.i2s_rx_buf[i]);

                chprintf((BaseSequentialStream*) &global.sercanmux1, " %d, %d\n", samples.size(), samples.back());
            }

            // if((global.i2s_rx_buf[i] == -1) || (global.i2s_rx_buf[i] == 0) )
            // {
            //      i--;
            // }

            // chprintf((BaseSequentialStream*) &global.sercanmux1, " %d, %d\n",
            //                  i, samples.at(i));

        }

        /*        if ((global.i2s_rx_buf[i] != 0) && (global.i2s_rx_buf[i] != -1) ) {

//              global.i2s_rx_buf[i] >>= 8;
              chprintf((BaseSequentialStream*) &global.sercanmux1, "%d, %d\n",
                        i, global.i2s_rx_buf[i]);
              meanval += global.i2s_rx_buf[i];
          }

      }*/
        float meanval = 0;
        for (int i=0; i<samples.size(); i++) {
            meanval += samples.at(i);
        }

        meanval /= samples.size();

        // subtract it from all sapmles to get a 'normalized' output

        for (int i=0; i<samples.size(); i++) {
            samples.at(i) -= meanval;
            //        chprintf((BaseSequentialStream*) &global.sercanmux1, " %d, %d\n",
            //                 i, samples.at(i));
        }

        uint32_t maxsample, minsample;
        minsample = -100000;
        maxsample = 100000;

        for (int i=0; i<samples.size(); i++) {
            minsample = std::min(minsample, samples.at(i));
            maxsample = std::max(maxsample,  samples.at(i));
        }

        //     chprintf((BaseSequentialStream*) &global.sercanmux1, " %d\n",
        //               ( maxsample - minsample));


        chprintf((BaseSequentialStream*) &global.sercanmux1,"stop exchange \n");
        chprintf((BaseSequentialStream*) &global.sercanmux1,"checking \n");

        this->sleep(MS2ST(1000));


    }

    // SHUTDOWN CODE

    return RDY_OK;
}
