<!-- Please do not change this logo with link -->
[![MCHP](images/microchip.png)](https://www.microchip.com)

# Getting Started with Universal Synchronous and Asynchronous Receiver and Transmitter (USART) Examples (Microchip Studio)

  This repository contains examples of bare metal source code for Universal Synchronous and Asynchronous Receiver and Transmitter (USART) as described in [TB3216-Universal Synchronous and Asynchronous Receiver and Transmitter (USART)](https://www.microchip.com/) document from Microchip. The repository contains an Microchip Studio Solution with multiple projects inside:

  * [<strong>Send Hello World:</strong>](Send_Hello_World) This use case demonstrates how to send a string to the PC via serial communication using the USART peripheral (for more details, see [<strong>Send Hello World</strong>](Send_Hello_World)).
  * [<strong>Send Formatted Strings Using 'printf':</strong>](Send_Formatted_Strings_Using_Printf) This use case shows how to send formatted strings through USART. This example sends the value of a counter every 500 ms and then increases it (for more details, see [<strong> Send Fromatted Strings Using 'printf'</strong>](Send_Formatted_String_Using_Printf)).
  * [<strong>Receive Control Commands:</strong>](Receive_Control_Commands) This use case shows how to implement a command line interface using the USART peripheral (for more details, see [<strong>Receive Control Commands</strong>](Receive_Control_Commands)).
  * [<strong>Synchronous Mode:</strong>](Synchronous_Mode) This use case demonstrates how to send one character using the USART synchronous mode (for more details, see [<strong>Synchronous Mode</strong>](Synchronous_Mode)).
  * [<strong>One-Wire Mode:</strong>](One_Wire_Mode) This use case demonstrates how to send a character string using the USART one wire mode (for more details, see [<strong>One-Wire Mode</strong>](One_Wire_Mode)).
  
## Related Documentation
More details and code examples on the ATMEGA4809 can be found at the following links:
- [TB3216-Getting Started with USART](https://ww1.microchip.com/downloads/en/Appnotes/TB3216-Getting-Started-with-USART-90003216B.pdf)
- [ATMEGA4809 Product Page](https://www.microchip.com/wwwproducts/en/ATMEGA4809)
- [ATMEGA4809 Code Examples on GitHub](https://github.com/microchip-pic-avr-examples?q=atmega4809)
- [ATMEGA4809 Project Examples in START](https://start.atmel.com/#examples/ATMEGA4809XplainedPro)


## Software Used
- Microchip Studio 7.0.2397 or newer [(microchip.com/mplab/microchip-studio)](https://www.microchip.com/mplab/microchip-studio)
- ATmega_DFP 1.5.362 or newer Device Pack


## Hardware Used
- ATMEGA4809 Xplained Pro [(ATMEGA4809-XPRO)](https://www.microchip.com/developmenttools/ProductDetails/ATMEGA4809-XPRO)
