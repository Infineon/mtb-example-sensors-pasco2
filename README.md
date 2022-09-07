# Connected Sensor Kit: PAS CO2 Application

This code example demonstrates how to use [Infineon XENSIV™ PAS CO2 sensor](https://www.infineon.com/cms/en/product/sensor/co2-sensors/) to measure the CO2 level.

## Features

- Ability to configure sampling interval for CO2 measurement

- Values given in CO2 parts per million (ppm)

[View this README on GitHub.](https://github.com/Infineon/mtb-example-sensors-pasco2)

[Provide feedback on this code example.](https://cypress.co1.qualtrics.com/jfe/form/SV_1NTns53sK2yiljn?Q_EED=eyJVbmlxdWUgRG9jIElkIjoiQ0UyMzI2MjMiLCJTcGVjIE51bWJlciI6IjAwMi0zMjYyMyIsIkRvYyBUaXRsZSI6IkNvbm5lY3RlZCBTZW5zb3IgS2l0OiBQQVMgQ08yIEFwcGxpY2F0aW9uIiwicmlkIjoid3V5YW5nIiwiRG9jIHZlcnNpb24iOiIxLjEuMCIsIkRvYyBMYW5ndWFnZSI6IkVuZ2xpc2giLCJEb2MgRGl2aXNpb24iOiJNQ0QiLCJEb2MgQlUiOiJTQlNZUyIsIkRvYyBGYW1pbHkiOiJTVUJTWVMifQ==)

## Requirements

- [ModusToolbox&trade; software](https://www.cypress.com/products/modustoolbox-software-environment) v2.4 or later (tested with v2.4)
- Board support package (BSP) minimum required version: 3.0.0
- Programming language: C
- Associated parts: All [PSoC&trade; 6 MCU](https://www.cypress.com/PSoC6) parts


## Supported toolchains (make variable 'TOOLCHAIN')

- GNU Arm® embedded compiler v10.3.1 (`GCC_ARM`) - Default value of `TOOLCHAIN`
- Arm&reg; compiler v6.13 (`ARM`)
- IAR C/C++ compiler v8.42.2 (`IAR`)


## Supported kits (make variable 'TARGET')

- Rapid IoT connect developer kit (`CYSBSYSKIT-DEV-01`) - Default value of `TARGET`
- [PSoC&trade; 4100S Plus prototyping kit](https://www.cypress.com/CY8CKIT-149) (`CY8CKIT-149`)

## Hardware setup

This code example requires the XENSIV™ PAS CO2 wing board as part of the connected sensor kit or PAS CO2 Sensor2Go Evaluation Kit connected to PSoC&trade; 4100S Plus prototyping kit.

1. Connect the PAS CO2 wing board to the CYSBSYSKIT-DEV-01 kit with the pin headers

   **Rapid IoT connect platform RP01 feather kit (CYSBSYSKIT-DEV-01)**

   ![](images/featherkit.png)

   **XENSIV™ PAS CO2 wing board**

   ![](images/featherwing.png)

   or Sensor2Go Evaluation Kit to PSoC&trade; prototyping kit as shown in the setup:

      **XENSIV™ PAS CO2 Sensor2Go kit with PSoC&trade; 4100S Plus prototyping kit**

   ![](images/pasco2-i2c-connection.png)

2. Connect the PSoC&trade; kit to the PC with a USB cable.

## Software setup

Install a terminal emulator if you don't have one. Instructions in this document use [Tera Term](https://ttssh2.osdn.jp/index.html.en).

This example requires no additional software or tools.


## Using the code example

Create the project and open it using one of the following:

<details><summary><b>In Eclipse IDE for ModusToolbox&trade; software</b></summary>

1. Click the **New Application** link in the **Quick Panel** (or, use **File** > **New** > **ModusToolbox Application**). This launches the [Project Creator](https://www.cypress.com/ModusToolboxProjectCreator) tool.

2. Pick a kit supported by the code example from the list shown in the **Project Creator - Choose Board Support Package (BSP)** dialog.

   When you select a supported kit, the example is reconfigured automatically to work with the kit. To work with a different supported kit later, use the [Library Manager](https://www.cypress.com/ModusToolboxLibraryManager) to choose the BSP for the supported kit. You can use the Library Manager to select or update the BSP and firmware libraries used in this application. To access the Library Manager, click the link from the **Quick Panel**.

   You can also just start the application creation process again and select a different kit.

   If you want to use the application for a kit not listed here, you may need to update the source files. If the kit does not have the required resources, the application may not work.

3. In the **Project Creator - Select Application** dialog, choose the example by enabling the checkbox.

4. (Optional) Change the suggested **New Application Name**.

5. The **Application(s) Root Path** defaults to the Eclipse workspace which is usually the desired location for the application. If you want to store the application in a different location, you can change the *Application(s) Root Path* value. Applications that share libraries should be in the same root path.

6. Click **Create** to complete the application creation process.

For more details, see the [Eclipse IDE for ModusToolbox&trade; software user guide](https://www.cypress.com/MTBEclipseIDEUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/ide_{version}/docs/mt_ide_user_guide.pdf*).

</details>

<details><summary><b>In command-line interface (CLI)</b></summary>

ModusToolbox&trade; software provides the Project Creator as both a GUI tool and the command line tool, "project-creator-cli". The CLI tool can be used to create applications from a CLI terminal or from within batch files or shell scripts. This tool is available in the *{ModusToolbox&trade; software install directory}/tools_{version}/project-creator/* directory.

Use a CLI terminal to invoke the "project-creator-cli" tool. On Windows, use the command line "modus-shell" program provided in the ModusToolbox&trade; software installation instead of a standard Windows command-line application. This shell provides access to all ModusToolbox&trade; software tools. You can access it by typing `modus-shell` in the search box in the Windows menu. In Linux and macOS, you can use any terminal application.

This tool has the following arguments:

Argument | Description | Required/optional
---------|-------------|-----------
`--board-id` | Defined in the `<id>` field of the [BSP](https://github.com/Infineon?q=bsp-manifest&type=&language=&sort=) manifest | Required
`--app-id`   | Defined in the `<id>` field of the [CE](https://github.com/Infineon?q=ce-manifest&type=&language=&sort=) manifest | Required
`--target-dir`| Specify the directory in which the application is to be created if you prefer not to use the default current working directory | Optional
`--user-app-name`| Specify the name of the application if you prefer to have a name other than the example's default name | Optional

<br>

The following example will clone the "[Sensors-PASCO2](https://github.com/Infineon/mtb-example-sensors-pasco2)" application with the desired name "SensorsPASCO2" configured for the *CYSBSYSKIT-DEV-01* BSP into the specified working directory, *C:/mtb_projects*:

   ```
   project-creator-cli --board-id CYSBSYSKIT-DEV-01 --app-id mtb-example-sensors-pasco2 --user-app-name SensorsPASCO2 --target-dir "C:/mtb_projects"
   ```

**Note:** The project-creator-cli tool uses the `git clone` and `make getlibs` commands to fetch the repository and import the required libraries. For details, see the "Project creator tools" section of the [ModusToolbox&trade; software user guide](https://www.cypress.com/ModusToolboxUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mtb_user_guide.pdf*).

</details>

<details><summary><b>In third-party IDEs</b></summary>

Use one of the following options:

- **Use the standalone [Project Creator](https://www.cypress.com/ModusToolboxProjectCreator) tool:**

   1. Launch Project Creator from the Windows Start menu or from *{ModusToolbox&trade; software install directory}/tools_{version}/project-creator/project-creator.exe*.

   2. In the initial **Choose Board Support Package** screen, select the BSP and click **Next**.

   3. In the **Select Application** screen, select the appropriate IDE from the **Target IDE** drop-down menu.

   4. Click **Create** and follow the instructions printed in the bottom pane to import or open the exported project in the respective IDE.

<br>

- **Use command-line interface (CLI):**

   1. Follow the instructions from the **In command-line interface (CLI)** section to create the application, and import the libraries using the `make getlibs` command.

   2. Export the application to a supported IDE using the `make <ide>` command.

   3. Follow the instructions displayed in the terminal to create or import the application as an IDE project.

For a list of supported IDEs and more details, see the "Exporting to IDEs" section of the [ModusToolbox&trade; software user guide](https://www.cypress.com/ModusToolboxUserGuide) (locally available at *{ModusToolbox&trade; software install directory}/docs_{version}/mtb_user_guide.pdf*).

</details>


## Operation

1. Connect the CYSBSYSKIT-DEV-01 kit with the CO2 wing board to the PC.

2. Open a terminal program and select the KitProg3 COM port. Set the serial port parameters to 8N1 and 115200 baud.

3. Program the board using one of the following:

   <details><summary><b>Using Eclipse IDE for ModusToolbox&trade; software</b></summary>

      1. Select the application project in the Project Explorer.

      2. In the **Quick Panel**, scroll down, and click **\<Application Name> Program (KitProg3_MiniProg4)**.
   </details>

   <details><summary><b>Using CLI</b></summary>

     From the terminal, execute the `make program` command to build and program the application using the default toolchain to the default target. The default toolchain and target are specified in the application's Makefile but you can override those values manually:
    ```
    make program TARGET=<BSP> TOOLCHAIN=<toolchain>
    ```

    Example:

    ```
    make program TARGET=CYSBSYSKIT-DEV-01 TOOLCHAIN=GCC_ARM
    ```

    </details>

4. After programming, the application starts automatically. Confirm that "Connected sensor kit: PAS CO2 application" is displayed on the UART terminal.

   **Figure 1. Terminal output on program startup**

   ![](images/terminal-co2.png)

    When the board is initialized successfully, the sensor information is provided through prints on the terminal as well as an onboard OK LED.

### Sensor information and LEDs

The sensor initialization process is indicated by blinking the red LED (`CYBSP_USER_LED`) on CYSBSYSKIT-DEV-01. The red LED (`CYBSP_USER_LED`) on CYSBSYSKIT-DEV-01 remains turned ON when system is operational (ready state); the OK LED on the PAS CO2 wing board is turned ON to show that the board is working normally. If this LED is OFF, check the connection with CYSBSYSKIT-DEV-01.

When the sensor gives a new value for CO2, it is displayed on the terminal. If a new value is not available, the state of the sensor is displayed on the terminal. If an out-of-range voltage or temperature error occurs, the warning LED on the CO2 wing board is turned ON. If the problem is resolved by the time of the next sample, the warning LED is turned OFF. The LED remaining ON indicates a problem with the voltage, temperature, or communication.

### Configurable parameters

You can configure the measurement period of the sensor. It is the sampling interval in seconds for the sensor to measure the CO2 level. Supported values range from 5 to 4095. The default value is 10 seconds.

For details, see the [pasco2 library API documentation](https://infineon.github.io/sensor-xensiv-pasco2/html/index.html).

## Debugging

You can debug the example to step through the code. In the IDE, use the **\<Application Name> Debug (KitProg3_MiniProg4)** configuration in the **Quick Panel**. For details, see the "Program and debug" section in the [Eclipse IDE for ModusToolbox&trade; software user guide](https://www.cypress.com/MTBEclipseIDEUserGuide).

**Note:** **(Only while debugging)** On the CM4 CPU, some code in `main()` may execute before the debugger halts at the beginning of `main()`. This means that some code executes twice – once before the debugger stops execution, and again after the debugger resets the program counter to the beginning of `main()`. See [KBA231071](https://community.cypress.com/docs/DOC-21143) to learn about this and for the workaround.


## Design and implementation

### Resources and settings

This example provides a possible way to use the *pasco2* library. It shows how to initialize the library and read the data from the sensor.

**Table 1. Application source files**

|**File name**            |**Comments**         |
| ------------------------|-------------------- |
| *main.c* |Has the application entry function. It sets up the BSP, global interrupts, and UART, and then initializes the controller tasks.|
| *pasco2_task.c* |Initializes the LEDs, power, and I2C enable switch for the PAS CO2 wing board. Has the task entry function for the pasco2 library.
| *pasco2_terminal_ui.c* | Has the task entry function for a simple version of the terminal UI configuration. |

<br>

**Table 2. Functions in *main.c***

| **Function name** | **Functionality** |
| ------------------------|-------------------- |
| `main` | Main function for the CM4 CPU. It does the following:<br>1. Initializes the BSP<br>2. Enables global interrupts<br>3. Initializes retarget IO<br>4. Creates the pasco2 task and terminal UI tasks<br>6. Starts the scheduler

<br>

**Table 3. Functions in *pasco2_task.c***

| **Function name** | **Functionality** |
| ------------------------|-------------------- |
| `pasco2_enable_internal_logging` | Enables/disables additional sensor information prints |
| `pasco2_display_ppm` | Enables the terminal output for the CO2 value |
| `pasco2_task` | Initializes LEDs, enables power, and the I2C communication channel of the PAS CO2 wing board, configures the PAS CO2 module, and starts reading the sensor values |

<br>

**Table 4. Functions in *pasco2_terminal_ui_task.c***

| **Function name** | **Functionality** |
| ------------------------|-------------------- |
| `terminal_ui_menu` | Prints the menu for parameter configuration |
| `terminal_ui_info` | Prints the help information |
| `terminal_ui_readline` | Gets the user input from the terminal |
| `pasco2_terminal_ui_task` | Starts the terminal UI task loop |

<br>

## Related resources

Resources  | Links
-----------|----------------------------------
Application notes  |[AN228571](https://www.cypress.com/AN228571) – Getting started with PSoC&trade; 6 MCU on ModusToolbox&trade; software
Code examples | [Using ModusToolbox&trade; software](https://github.com/Infineon/Code-Examples-for-ModusToolbox-Software) on GitHub
Device documentation | [PSoC&trade; 6 MCU datasheets](https://www.cypress.com/search/all?f[0]=meta_type%3Atechnical_documents&f[1]=resource_meta_type%3A575&f[2]=field_related_products%3A114026) <br> [PSoC&trade; 6 technical reference manuals](https://www.cypress.com/search/all/PSoC%206%20Technical%20Reference%20Manual?f[0]=meta_type%3Atechnical_documents&f[1]=resource_meta_type%3A583)
Development kits | [Connected sensor kit](https://www.infineon.com/connectedsensorkit) <br> CYSBSYSKIT-DEV-01 rapid IoT connect developer kit
Libraries on GitHub  | [mtb-pdl-cat1](https://github.com/Infineon/mtb-pdl-cat1) – PSoC&trade; 6 peripheral driver library (PDL)  <br> [mtb-hal-cat1](https://github.com/Infineon/mtb-hal-cat1) – Hardware abstraction layer (HAL) library <br> [retarget-io](https://github.com/Infineon/retarget-io) – Utility library to retarget STDIO messages to a UART port <br> [sensor-xensiv-pasco2](https://github.com/Infineon/sensor-xensiv-pasco2) – PAS CO2 library API to configure the PAS CO2 sensor and get ppm values  <br>  [sensor-xensiv-dps3xx](https://github.com/Infineon/sensor-xensiv-dps3xx) – DPS3xx library API to configure the DPS3xx sensor and get the pressure and temperature values
Middleware on GitHub  | [psoc6-middleware](https://github.com/Infineon/modustoolbox-software#psoc-6-middleware-libraries) – Links to all PSoC&trade; 6 MCU middleware
Tools  | [Eclipse IDE for ModusToolbox&trade; software](https://www.cypress.com/modustoolbox): ModusToolbox&trade; software is a collection of easy-to-use software and tools enabling rapid development with Infineon MCUs, covering applications from embedded sense and control to wireless and cloud-connected systems using AIROC&trade; Wi-Fi and Bluetooth® connectivity devices.

<br>

## Other resources

Cypress provides a wealth of data at www.cypress.com to help you select the right device, and quickly and effectively integrate it into your design.

For PSoC&trade; 6 MCU devices, see [How to design with PSoC&trade; 6 MCU - KBA223067](https://community.cypress.com/docs/DOC-14644) in the Cypress community.


## Document history

Document title: *CE232623* – *Connected Sensor Kit: PAS CO2 Application*

 Version | Description of change
 ------- | ---------------------
 0.5.0   | New code example
 1.0.0   | Update to use XENSIV™ PAS CO2 driver 1.0.0 and XENSIV™ DPS3xx 1.0.0
 1.1.0   | Added support for PSoC&trade; 4100S Plus prototyping kit. <br> Added support for Arm&reg; and IAR compilers

<br />

---------------------------------------------------------

© Cypress Semiconductor Corporation, 2021-2022. This document is the property of Cypress Semiconductor Corporation, an Infineon Technologies company, and its affiliates ("Cypress").  This document, including any software or firmware included or referenced in this document ("Software"), is owned by Cypress under the intellectual property laws and treaties of the United States and other countries worldwide.  Cypress reserves all rights under such laws and treaties and does not, except as specifically stated in this paragraph, grant any license under its patents, copyrights, trademarks, or other intellectual property rights.  If the Software is not accompanied by a license agreement and you do not otherwise have a written agreement with Cypress governing the use of the Software, then Cypress hereby grants you a personal, non-exclusive, nontransferable license (without the right to sublicense) (1) under its copyright rights in the Software (a) for Software provided in source code form, to modify and reproduce the Software solely for use with Cypress hardware products, only internally within your organization, and (b) to distribute the Software in binary code form externally to end users (either directly or indirectly through resellers and distributors), solely for use on Cypress hardware product units, and (2) under those claims of Cypress’s patents that are infringed by the Software (as provided by Cypress, unmodified) to make, use, distribute, and import the Software solely for use with Cypress hardware products.  Any other use, reproduction, modification, translation, or compilation of the Software is prohibited.
<br>
TO THE EXTENT PERMITTED BY APPLICABLE LAW, CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH REGARD TO THIS DOCUMENT OR ANY SOFTWARE OR ACCOMPANYING HARDWARE, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  No computing device can be absolutely secure.  Therefore, despite security measures implemented in Cypress hardware or software products, Cypress shall have no liability arising out of any security breach, such as unauthorized access to or use of a Cypress product. CYPRESS DOES NOT REPRESENT, WARRANT, OR GUARANTEE THAT CYPRESS PRODUCTS, OR SYSTEMS CREATED USING CYPRESS PRODUCTS, WILL BE FREE FROM CORRUPTION, ATTACK, VIRUSES, INTERFERENCE, HACKING, DATA LOSS OR THEFT, OR OTHER SECURITY INTRUSION (collectively, "Security Breach").  Cypress disclaims any liability relating to any Security Breach, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any Security Breach.  In addition, the products described in these materials may contain design defects or errors known as errata which may cause the product to deviate from published specifications. To the extent permitted by applicable law, Cypress reserves the right to make changes to this document without further notice. Cypress does not assume any liability arising out of the application or use of any product or circuit described in this document. Any information provided in this document, including any sample design information or programming code, is provided only for reference purposes.  It is the responsibility of the user of this document to properly design, program, and test the functionality and safety of any application made of this information and any resulting product.  "High-Risk Device" means any device or system whose failure could cause personal injury, death, or property damage.  Examples of High-Risk Devices are weapons, nuclear installations, surgical implants, and other medical devices.  "Critical Component" means any component of a High-Risk Device whose failure to perform can be reasonably expected to cause, directly or indirectly, the failure of the High-Risk Device, or to affect its safety or effectiveness.  Cypress is not liable, in whole or in part, and you shall and hereby do release Cypress from any claim, damage, or other liability arising from any use of a Cypress product as a Critical Component in a High-Risk Device. You shall indemnify and hold Cypress, including its affiliates, and its directors, officers, employees, agents, distributors, and assigns harmless from and against all claims, costs, damages, and expenses, arising out of any claim, including claims for product liability, personal injury or death, or property damage arising from any use of a Cypress product as a Critical Component in a High-Risk Device. Cypress products are not intended or authorized for use as a Critical Component in any High-Risk Device except to the limited extent that (i) Cypress’s published data sheet for the product explicitly states Cypress has qualified the product for use in a specific High-Risk Device, or (ii) Cypress has given you advance written authorization to use the product as a Critical Component in the specific High-Risk Device and you have signed a separate indemnification agreement.
<br>
Cypress, the Cypress logo, and combinations thereof, WICED, ModusToolbox, PSoC, CapSense, EZ-USB, F-RAM, and Traveo are trademarks or registered trademarks of Cypress or a subsidiary of Cypress in the United States or in other countries. For a more complete list of Cypress trademarks, visit cypress.com. Other names and brands may be claimed as property of their respective owners.
