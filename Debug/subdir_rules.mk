################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
ADC_Function.obj: ../ADC_Function.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/CodeComposer/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/utils" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/driverlib" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/inc" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c123gxl" --include_path="D:/CodeComposer/WorkSpace/Ae2Can" --include_path="D:/CodeComposer/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --define=ccs="ccs" --define=PART_TM4C1231D5PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="ADC_Function.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

CAN_Function.obj: ../CAN_Function.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/CodeComposer/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/utils" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/driverlib" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/inc" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c123gxl" --include_path="D:/CodeComposer/WorkSpace/Ae2Can" --include_path="D:/CodeComposer/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --define=ccs="ccs" --define=PART_TM4C1231D5PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="CAN_Function.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

InitialConfiguration.obj: ../InitialConfiguration.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/CodeComposer/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/utils" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/driverlib" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/inc" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c123gxl" --include_path="D:/CodeComposer/WorkSpace/Ae2Can" --include_path="D:/CodeComposer/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --define=ccs="ccs" --define=PART_TM4C1231D5PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="InitialConfiguration.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Loop_Functions.obj: ../Loop_Functions.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/CodeComposer/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/utils" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/driverlib" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/inc" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c123gxl" --include_path="D:/CodeComposer/WorkSpace/Ae2Can" --include_path="D:/CodeComposer/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --define=ccs="ccs" --define=PART_TM4C1231D5PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="Loop_Functions.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

UART_Function.obj: ../UART_Function.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/CodeComposer/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/utils" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/driverlib" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/inc" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c123gxl" --include_path="D:/CodeComposer/WorkSpace/Ae2Can" --include_path="D:/CodeComposer/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --define=ccs="ccs" --define=PART_TM4C1231D5PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="UART_Function.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/CodeComposer/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/utils" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/driverlib" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/inc" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c123gxl" --include_path="D:/CodeComposer/WorkSpace/Ae2Can" --include_path="D:/CodeComposer/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --define=ccs="ccs" --define=PART_TM4C1231D5PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

tm4c1231d5pm_startup_ccs.obj: ../tm4c1231d5pm_startup_ccs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"D:/CodeComposer/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/utils" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/driverlib" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/inc" --include_path="D:/CodeComposer/ti/TivaWare_C_Series-2.1.4.178/examples/boards/ek-tm4c123gxl" --include_path="D:/CodeComposer/WorkSpace/Ae2Can" --include_path="D:/CodeComposer/ti/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS/include" --define=ccs="ccs" --define=PART_TM4C1231D5PM -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="tm4c1231d5pm_startup_ccs.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


