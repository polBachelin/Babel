/*
** EPITECH PROJECT, 2021
** Babel
** File description:
** main
*/

#include <iostream>
#include "portaudio.h"


int main(void)
{
    std::cout << "Sa roule ma couille ?\nça farte?";
    
    int     i, numDevices, defaultDisplayed;
      const   PaDeviceInfo *deviceInfo;
      PaStreamParameters inputParameters, outputParameters;
      PaError err;
  
      
      err = Pa_Initialize();
      if( err != paNoError )
      {
          printf( "ERROR: Pa_Initialize returned 0x%x\n", err );
          return 84;
      } 
      
      printf( "PortAudio version: 0x%08X\n", Pa_GetVersion());
      printf( "Version text: '%s'\n", Pa_GetVersionInfo()->versionText );
  
      numDevices = Pa_GetDeviceCount();
      if( numDevices < 0 )
      {
          printf( "ERROR: Pa_GetDeviceCount returned 0x%x\n", numDevices );
          err = numDevices;
          return 84;
      }
      
      printf( "Number of devices = %d\n", numDevices );
      for( i=0; i<numDevices; i++ )
      {
          deviceInfo = Pa_GetDeviceInfo( i );
          printf( "--------------------------------------- device #%d\n", i );
                  
      /* Mark global and API specific default devices */
          defaultDisplayed = 0;
          if( i == Pa_GetDefaultInputDevice() )
          {
              printf( "[ Default Input" );
              defaultDisplayed = 1;
          }
          else if( i == Pa_GetHostApiInfo( deviceInfo->hostApi )->defaultInputDevice )
          {
              const PaHostApiInfo *hostInfo = Pa_GetHostApiInfo( deviceInfo->hostApi );
              printf( "[ Default %s Input", hostInfo->name );
              defaultDisplayed = 1;
          }
          
          if( i == Pa_GetDefaultOutputDevice() )
          {
              printf( (defaultDisplayed ? "," : "[") );
              printf( " Default Output" );
              defaultDisplayed = 1;
          }
          else if( i == Pa_GetHostApiInfo( deviceInfo->hostApi )->defaultOutputDevice )
          {
              const PaHostApiInfo *hostInfo = Pa_GetHostApiInfo( deviceInfo->hostApi );
              printf( (defaultDisplayed ? "," : "[") );                
              printf( " Default %s Output", hostInfo->name );
              defaultDisplayed = 1;
          }
      }
          if( defaultDisplayed )
              printf( " ]\n" );
  
      Pa_Terminate();
  
      printf("----------------------------------------------\n");
      
    return 0;
}