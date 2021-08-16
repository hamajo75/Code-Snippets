
package hw;

import java.lang.*;

public class IOException extends Exception
{
	public static final int E_COMMAND =					1001;
	public static final int E_NOT_BOOLEAN =         1004;

	public static final int E_IO_BAUDRATE =			1016;	
	public static final int E_IO_COMPORT =				1017;	
	public static final int E_IO_LEDPAR =				1018;	
	public static final int E_IO_LEDDEFINED =			1019;	
	public static final int E_IO_LEDMODE =				1020;	
	public static final int E_IO_ADCCHANNEL =		 	1021;	
	public static final int E_IO_ADCENABLE =		  	1022;	
	public static final int E_IO_FREQU =				1023;	
	public static final int E_IO_DUTY =					1024;	
	public static final int E_IO_REL_NUMBER =			1025;	
	public static final int E_IO_REL_MODE =			1026;	
	public static final int E_IO_RTC_READ =			1027;	
	public static final int E_IO_RTC_WRITE =			1028;	
	public static final int E_IO_TM_HOUR =				1029;	
	public static final int E_IO_TM_MINUTE =			1030;	
	public static final int E_IO_TM_SECOND =			1031;	
	public static final int E_IO_DT_MONTH =			1032;	
	public static final int E_IO_DT_DAY =				1033;	
	public static final int E_IO_DT_DAYOFWEEK =		1034;
	
	public static final int E_IO_CRON_EDGE =  		1035;
	public static final int E_IO_CRON_CNT =			1036;
	public static final int E_IO_CRON_PIN =			1037;
	public static final int E_IO_CRON_ENABLE =		1038;
	public static final int E_IO_CRON_NO_VALUE =		1039;
	public static final int E_IO_CRON_CNT_OV =		1040;
	public static final int E_IO_CRON_NOT_OPEN =		1041;
	public static final int E_IO_CRON_TURNED_OFF =  1042;
	
	public static final int E_IO_ROTARY_TIMEVAL =	1043;	
	public static final int E_IO_ROTARY_ENABLED =	1044;
	
	public static final int E_IO_PWM_PIN =				1045;
	public static final int E_IO_PWM_PORT_PIN =		1046;
	public static final int E_IO_PWM_FREQ =			1047;
	public static final int E_IO_PWM_DUTY_CYCLE =	1048;
	public static final int E_IO_PWM_ON_OFF =      	1049;
	public static final int E_IO_PWM_RESOLUTION =   1050;

	private final int errorCode;

	public IOException(int code)
	{
		super(codeToDescription(code));
		this.errorCode = code;
	}
	
	public IOException(String description)
	{
		super(description);
		this.errorCode = -1;
	}

	public int getErrorCode()
	{
		return this.errorCode;
	}

	private static String codeToDescription(int code)
	{
		String description = "Unknown error code!";
		switch (code)
		{
			case E_COMMAND:
				description = "specified parameter is out of range";
				break;
			case E_NOT_BOOLEAN:
				description = "specified parameter is not a boolean";
				break;
				
			case E_IO_BAUDRATE:
				description = "Invalid baudrate specified";
				break;
			case E_IO_COMPORT:
				description = "Invalid com port specified";
				break;
			case E_IO_LEDPAR:
				description = "Output number out of range";
				break;
			case E_IO_LEDDEFINED:
				description = "Output not defined";
				break;
			case E_IO_LEDMODE:
				description = "Invalid output mode";
				break;
			case E_IO_ADCCHANNEL:
				description = "Adc channel out of range";
				break;
			case E_IO_ADCENABLE:
				description = "Adc channel not enabled";
				break;
			case E_IO_FREQU:
				description = "Frequency out of range";
				break;
			case E_IO_DUTY:
				description = "Duty cycle out of range";
				break;
			case E_IO_REL_NUMBER:
				description = "Relay number out of range";
				break;
			case E_IO_REL_MODE:
				description = "Invalid relay mode specified";
				break;
			case E_IO_RTC_READ:
				description = "RTC read error";
				break;
			case E_IO_RTC_WRITE:
				description = "RTC write error";
				break;
			case E_IO_TM_HOUR:
				description = "Invalid hour specified";
				break;
			case E_IO_TM_MINUTE:
				description = "Invalid minute specified";
				break;
			case E_IO_TM_SECOND:
				description = "Invalid second specified";
				break;
			case E_IO_DT_MONTH:
				description = "Invalid month specified";
				break;
			case E_IO_DT_DAY:
				description = "Invalid day specified";
				break;
			case E_IO_DT_DAYOFWEEK:
				description = "Invalid day of week specified";
				break;				
			case E_IO_CRON_EDGE:
				description = "Invalid edge value specified";
				break;
			case E_IO_CRON_CNT:
				description = "Invalid edge count value specified";
				break;
			case E_IO_CRON_PIN:
				description = "Invalid input pin specified, please select another input within the 'Settings'";
				break;
			case E_IO_CRON_ENABLE:
				description = "Invalid onOff value specified to enable or disable chronometry";
				break;
			case E_IO_CRON_NO_VALUE:
				description = "No new value available";
				break;
			case E_IO_CRON_CNT_OV:
				description = "Counter overflow has occurred";
				break;
			case E_IO_CRON_NOT_OPEN:
				description = "Chronometry is not open";
				break;
			case E_IO_CRON_TURNED_OFF:
				description = "Chronometry is turned off";
				break;							
			case E_IO_ROTARY_TIMEVAL:
				description = "Invalid rotary timeout value (ranging from 2 to 25)";
				break;
			case E_IO_ROTARY_ENABLED:
				description = "Rotary encoder is not enabled, please enable it within the 'Settings'";
				break;
							
			case E_IO_PWM_PIN:
				description = "Invalid pwm pin specified";
				break;				
			case E_IO_PWM_PORT_PIN:
				description = "Invalid pwm port pin specified, please select another pwm pin within the 'Settings'";
				break;				
			case E_IO_PWM_FREQ:
				description = "Invalid pwm frequency specified (ranging from 1 to 10000000)";
				break;				
			case E_IO_PWM_DUTY_CYCLE:
				description = "Invalid pwm duty cycle specified (ranging from 0 to IO.getPWMDutyCycleResolution())";
				break;			
			case E_IO_PWM_ON_OFF:
				description = "Invalid pwm on off parameter specified (ranging from 1 to 2)";
				break;
			case E_IO_PWM_RESOLUTION:
				description = "Invalid pwm resolution parameter specified (value > 0)";
				break;
		}
		return description;
	}
}
