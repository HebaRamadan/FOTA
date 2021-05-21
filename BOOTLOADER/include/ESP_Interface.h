/*
 * ESP_Interface.h
 *
 *  Created on: Feb 24, 2021
 *      Author: zas
 */

#ifndef ESP_INTERFACE_H_
#define ESP_INTERFACE_H_

void ESP_vidInit(void);
void ESP_vidConnectWiFi      ( u8 * Copy_u8Name      ,  u8 * Copy_u8Pasword );
void ESP_vidConnectServerTCP ( u8 * Copy_u8ServerIP  ,  u8 * Copy_u8Port    );
void ESP_vidGetPageFromServer( u8   Copy_u8PageNum  );

void ESP_vidControlUploading( u8 Copy_u8DownloadFlag );
void ESP_vidGetMetaData(void);

void ESP_vidClearBuffer (void);
void MUSART1_CallBackFunction(void);

#define MAX_LINES     30
#define MAX_CHARS     45



#endif /* ESP_INTERFACE_H_ */
