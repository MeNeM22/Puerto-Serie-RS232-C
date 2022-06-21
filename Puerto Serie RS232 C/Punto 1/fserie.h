#include <windows.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <string>


/*#include <windows.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>*/

using namespace std;
//  uses windows,sysutils,forms,dialogs,extctrls;



	 HANDLE			hport;				//Fichier de sortie sur le port COM		| The file stream use for acces to the serial port.
	_COMMTIMEOUTS	ct;                 //={0,0,0,0,0}; //Config du Time Out	| This variable contain the delay of the time-out.
	DCB				dcbport;				//Config du Port						| This object is use in order to configure the serial port.
	int				bufferSize;




bool initserie(unsigned char np,long velo);
//bool initserieshared(unsigned char np,int velo);
void closeserie();

//int GetInCount();
void vaciar();

bool seriereadstr(void *sdata, DWORD nbytes);
//bool recibex(char *data, DWORD nbytes,bool *boolean);
bool seriewritestr(string sdata);
//bool enviax(const char *sData, bool  &abortar);
bool setTimeOut(DWORD ms);
bool cambiarts(bool val);
bool cambiadtr(bool val);
bool cambiatxd(bool val);

bool vercts();

bool verdtr();
bool verring();
bool verdcd();


bool initserie(unsigned char np,long velo)
 {
   char sCom[6]="COM";
   char buffnp[3];


   char sErrMsg[10];


   // close port if open already

   if(hport != INVALID_HANDLE_VALUE)
		  closeserie();
	//try to open the port }
	 itoa(np,buffnp,10);


		  strcat(sCom,buffnp);




		hport = CreateFile(sCom, GENERIC_READ | GENERIC_WRITE, 0, NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,0L);

				if(hport==0 || hport==INVALID_HANDLE_VALUE)
								  return false;
				setTimeOut(200);//decia 100


				if ( !SetupComm(hport, bufferSize, bufferSize) )
								 return false;

				 if ( !GetCommState(hport, &dcbport))
						  return false;


			//fill in the fields of the structure }
			dcbport.BaudRate = velo;
			dcbport.ByteSize = 8;
			dcbport.Parity = NOPARITY;
			dcbport.StopBits = ONESTOPBIT;
			///****dcbPort.Flags = 0;




	 if (!SetCommState(hport, &dcbport))
		return false;
	  else
		return true;



	}




/*	bool initserieshared(unsigned char np,int velo)
 {
   char sCom[10];
   char bufnp[3];
   TDCB dcbPort;
   bool boolAbort;
   char sErrMsg[10];
   boolAbort=true;
   lBaud=velo;
   // close port if open already
   if(hPort != INVALID_HANDLE_VALUE)
		  closeserie();
	//try to open the port }
	 itoa(np,bufnp,10);
	 do
	   {        strcpy(sCom,"COM"),

				strcat(sCom,bufnp);
		//sCom = "COM" + IntToStr(np);/si sCom es de tipo AnsiString



		hPort = CreateFile(sCom, GENERIC_READ | GENERIC_WRITE,FILE_SHARE_WRITE | FILE_SHARE_READ , NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,0L);


				setTimeOut(100);
				if ((hPort == INVALID_HANDLE_VALUE)&&(boolShowErrors))
		{
					ShowMessage("Error");

			   /*	if (MessageDlg("Error al tratar de abrir el puerto COM" + IntToStr(np) + ":" + sErrMsg,mtWarning, [mbAbort, mbRetry], 0))== idAbort)
				boolAbort = true;
			else
			   boolAbort = false;*/
		//}

	/*}
		while((hPort == INVALID_HANDLE_VALUE) && (boolAbort == false));

	//set the baud rate and other parameters
	if (hPort != INVALID_HANDLE_VALUE)
	{
		if( GetCommState(hPort, &dcbPort))
		{
			// fill in the fields of the structure }
			dcbPort.BaudRate = lBaud;
			dcbPort.ByteSize = 8;
			dcbPort.Parity = NOPARITY;
			dcbPort.StopBits = ONESTOPBIT;
			//*****dcbPort.Flags = 0;
			/* flag bit fields:
			dcb_Binary, dcb_Parity, dcb_OutxCtsFlow, dcb_fOutxDsrFlow,
			dcb_fOutX, dcb_fInX, dcb_DtrFlow, dcb_RtsFlow
			*/
		/*	SetCommState(hPort, &dcbPort);
		}
	}



	   // return True if handle is valid
	 return(hPort != INVALID_HANDLE_VALUE);
	//boolInUse := False;


 }*/

 // Close the COM port



void closeserie()
{	if(hport != INVALID_HANDLE_VALUE)
		   CloseHandle(hport);
	hport = INVALID_HANDLE_VALUE;

}





bool setTimeOut(DWORD ms)
 {

 //--- Vérification des paramétres passés à la fonction:
 if(ms<0)
  return(false);
 else
 {
  ct.ReadIntervalTimeout = 0;
  ct.ReadTotalTimeoutMultiplier = 0; // pas de multipicateur de timeout en onction du nombre de caractères demandés.
  ct.ReadTotalTimeoutConstant = ms;
  ct.WriteTotalTimeoutMultiplier = 0;
  ct.WriteTotalTimeoutConstant = ms;
  if(! SetCommTimeouts(hport, &ct))//Configuration du Time Out
	return(false);
  }
  return(true);
 //MSDN: The SetCommTimeouts function sets the time-out parameters for all read nd write operations on a specified communications device.

}




bool seriewritestr(string sdata)
{
 DWORD dwCharsWritten;
 bool resu;


  dwCharsWritten = 0;
  resu = false; // default to error return

  if( hport != INVALID_HANDLE_VALUE)
	   {
	WriteFile(hport,sdata.c_str(),sdata.length() , &dwCharsWritten, NULL);
	if( dwCharsWritten == sdata.length())
		 resu = true;
	}



   return(resu);

}



bool seriereadstr( void  *sdata,DWORD nbytes)
{
 DWORD nbytesleidos;
 bool resu;
 nbytesleidos=0;
 //char *paux;
 /*if( (nbytes <=0)||((data->c_str())==NULL))
  return(false);*/
if(nbytes <=0)
   return(false);

 //data->SetLength(nbytes+1);
 //paux = new char[nbytes+1];

 resu=ReadFile(hport,sdata , nbytes,&nbytesleidos ,NULL);
 if ((!resu)||(nbytes < nbytesleidos))  //decia >
  {

   return(false);

  }
 else
  {

   return(true);
  }


}



 bool cambiarts(bool val)
 {
  if(val == true)
	{

	 if(EscapeCommFunction(hport,SETRTS))
		return(true);
	 else
		return(false);
	 }
	 else{
			 if(EscapeCommFunction(hport,CLRRTS))
				return(true);
			 else
				return(false);


		  }
 }





 //**************************** cambiadtr(val) *************************************************
// **** cambia DTR a  0 u 1


 bool cambiadtr(bool val)
 {
  if(val == true)
	{

	 if(EscapeCommFunction(hport,SETDTR))
		return(true);
	 else
		return(false);
	 }
	 else{
			 if(EscapeCommFunction(hport,CLRDTR))
				return(true);
			 else
				return(false);


		  }
 }


//*******function cambiatxd(val);****************
//cambia txd a 0 o 1*****************


  bool cambiatxd(bool val)
 {
  if(val == true)
	{

	 if(EscapeCommFunction(hport,SETBREAK))
		return(true);
	 else
		return(false);
	 }
	 else{
			 if(EscapeCommFunction(hport,CLRBREAK))
				return(true);
			 else
				return(false);


		  }
 }






 //********************** GetCts() ***********************/

 bool vercts()
 { DWORD resu;
   GetCommModemStatus(hport,&resu);
   if((resu & MS_CTS_ON) != 0)
	 return(true);
   else
	return(false);

 }

 bool verdtr()
 { DWORD resu;
   GetCommModemStatus(hport,&resu);
   if((resu & MS_DSR_ON) != 0)
	 return(true);
   else
	return(false);

 }


 bool verring()
 { DWORD resu;
   GetCommModemStatus(hport,&resu);
   if((resu & MS_RING_ON) != 0)
	 return(true);
   else
	return(false);

 }

 bool verdcd()
 { DWORD resu;
   GetCommModemStatus(hport,&resu);
   if((resu & MS_RLSD_ON) != 0)
	 return(true);
   else
	return(false);

 }

 string getErrorMsg()
{
	LPVOID lpMsgBuf;
	string error = "";

	if ( FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
							NULL, GetLastError(),
							MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
							(LPTSTR) &lpMsgBuf, 0, NULL ))
	{
		error.assign((LPCTSTR)lpMsgBuf);
	}

	return error;
}
