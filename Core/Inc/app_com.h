#ifndef _APP_COM_H_
#define _APP_COM_H_

extern volatile uint8_t points_data_usb_tx[];

extern volatile uint8_t time_to_send_data_through_usb;

void usb_send_data(void);

void usb_task(void);


#endif /* _APP_COM_H_ */
