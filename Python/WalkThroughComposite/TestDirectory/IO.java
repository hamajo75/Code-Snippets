package hw;

import javax.events.EventManagement;
import java.io.*;

public final class IO
{
	private IO()
	{}

	public static final byte PORT_ID_SERIAL_CURRENT     = 0;
	public static final byte PORT_ID_SERIAL_0           = 1;
	public static final byte PORT_ID_SERIAL_1           = 2;
	public static final byte PORT_ID_USB                = 3;
	public static final byte PORT_ID_I2C                = 4;
	public static final byte PORT_ID_SPI                = 5;
	public static final byte PORT_ID_ETHERNET           = 6;
	public static final byte PORT_SERIAL_0              = 1 << 1;
	public static final byte PORT_SERIAL_1              = 1 << 2;
	public static final byte PORT_USB                   = 1 << 3;
	public static final byte PORT_I2C                   = 1 << 4;
	public static final byte PORT_SPI                   = 1 << 5;
	public static final byte PORT_ETHERNET              = 1 << 6;
	public static final byte ANALOG_IN_0                = 0;
	public static final byte ANALOG_IN_1                = 1;
	public static final byte ANALOG_IN_2                = 2;
	public static final byte ANALOG_IN_3                = 3;
	public static final byte OUTPUT_SET_TO_OFF          = 0;
	public static final byte OUTPUT_SET_TO_ON           = 1;
	public static final byte OUTPUT_SET_TO_BLINK        = 2;
	public static final byte RELAY_0                    = 0;
	public static final byte RELAY_1                    = 1;
	public static final byte RELAYS_SET_OFF             = 0;
	public static final byte RELAYS_SET_ON              = 1;
	public static final byte RELAYS_ENABLE_PWM_ON_RELAY = 2;
	static final byte KEYBOARD_COLUMNS                  = 0x10;
	static final byte KEYBOARD_ROWS	                   = 8;	
	
	public static final byte INPUT_0                    = 0;
	public static final byte INPUT_1                    = 1;
	public static final byte INPUT_2                    = 2;
	public static final byte INPUT_3                    = 3;
	public static final byte INPUT_4                    = 4;
	public static final byte INPUT_5                    = 5;
	public static final byte INPUT_6                    = 6;
	public static final byte INPUT_7                    = 7;
	public static final byte INPUT_8                    = 8;
	public static final byte INPUT_9                    = 9;
	public static final byte INPUT_10                   = 10;
	public static final byte INPUT_11                   = 11;
	public static final byte INPUT_12                   = 12;
	public static final byte INPUT_13                   = 13;
	public static final byte INPUT_14                   = 14;
	public static final byte INPUT_15                   = 15;	
	public static final byte CHRON_ON                   = 1;
	public static final byte CHRON_OFF                  = 2;	
	public static final byte RISING_EDGE                = 1;
	public static final byte FALLING_EDGE               = 2;	

	private static final int E_NOERR = 0;
	private static int rotaryEncoderPeriod					 = 2;

	public static void enableDisableCommunicationPorts(int portMask, int timeout) throws IOException	
	{
		int errorCode = enableDisableCommunicationPortsN((byte) portMask, (short) timeout);

		if (E_NOERR != errorCode)
			throw new IOException("Unknown error code!");
	}

	public static void setKeyboardEnabled(boolean enabled) throws IOException
	{
		int errorCode = enableDisableKeyboardN(Conversion.boolToByte(enabled));

		if (E_NOERR != errorCode)
			throw new IOException(errorCode);
	}

	public static void setKeyboardReportingEnabled(boolean enabled) throws IOException
	{
		int errorCode = enableDisableKeyboardReportingN(Conversion.boolToByte(enabled));
		
		if (E_NOERR != errorCode)
			throw new IOException(errorCode);
		
		EventManagement.start();
	}

	public static void setRotaryEncoderEnabled(boolean enabled) throws IOException
	{
		int errorCode = enableDisableRotaryEncoderN(Conversion.boolToByte(enabled));
	
		if (E_NOERR != errorCode)
			throw new IOException(errorCode);
			
		setRotaryEncoderPeriod(rotaryEncoderPeriod);
	}

	public static void setRotaryEncoderReportingEnabled(boolean enabled) throws IOException
	{
		int errorCode = enableDisableRotaryEncoderReportingN(Conversion.boolToByte(enabled));
	
		if (E_NOERR != errorCode)
			throw new IOException(errorCode);

		EventManagement.start();
	}
	
	public static byte getRotaryEncoderValue() throws IOException
	{
		byte[] value  = new byte[2];
		int errorCode = getRotaryEncoderValueN(value);
		
		if (E_NOERR != errorCode)
			throw new IOException(errorCode);
		
		return value[0];
	}
	
	public static void setRotaryEncoderPeriod(int value) throws IOException
	{
		int errorCode = setRotaryEncoderTimeoutN(value);
		
		if (errorCode != 0)
			throw new IOException(errorCode);
			
		rotaryEncoderPeriod = value;
	}	

	public static int getADCValue(int port) throws IOException
	{
		byte[] data = new byte[2];

		int errorCode = getADCValueN((byte) port, data);
		
		if (E_NOERR != errorCode)
			throw new IOException(errorCode);

		return Conversion.wordToUnsignedInt(data);
	}

	public static int getCurrentCommunicationPort() throws IOException	
	{
		byte[] data = new byte[2];

		int errorCode = getCurrentCommunicationPortN(data);
		
		if (E_NOERR != errorCode)
			throw new IOException("Unknown error code!");

		return Conversion.wordToUnsignedInt(data, Conversion.SWAP_ELEMENTS);
	}

	public static Date getDate() throws IOException
	{
		byte[] data = new byte[4];

		int errorCode = getDateN(data);
		
		if (E_NOERR != errorCode)
			throw new IOException("Unknown error code!");
		
		return new Date(	
								Conversion.byteToUnsignedInt(data[0]), 			// year
								Conversion.byteToUnsignedInt(data[1]), 			// month
								Conversion.byteToUnsignedInt(data[2]), 			// day
								Conversion.byteToUnsignedInt(data[3])				// weekDay
							);
	}
	
	public static DateTime getDateTime() throws IOException
	{
		Date date = IO.getDate();
		Time time = IO.getTime();

		return new DateTime(date, time);
	}

	public static int getEnabledCommunicationPorts() throws IOException
	{
		byte[] data = new byte[2];

		int errorCode = getEnabledCommunicationPortsN(data);
		
		if (E_NOERR != errorCode)
			throw new IOException("Unknown error code!");
		
		return Conversion.wordToUnsignedInt(data, Conversion.SWAP_ELEMENTS);
	}
	
	public static int getInputsState() throws IOException
	{
		byte[] data = new byte[4];

		int errorCode = getInputsStateN(data);
		if (E_NOERR != errorCode)
			throw new IOException("Unknown error code!");
		
		return Conversion.dwordToInt(data);
	}

	public static int[] getKeyboardState() throws IOException
	{
		int[] keyboardState = new int[KEYBOARD_COLUMNS];

		int errorCode = getKeyboardStateN(keyboardState);
		
		if (E_NOERR != errorCode)
			throw new IOException(errorCode);
		
		return keyboardState;				
	}

	public static Time getTime() throws IOException
	{
		byte[] data = new byte[3];

		int errorCode = getTimeN(data);
		
		if (E_NOERR != errorCode)
			throw new IOException("Unknown error code!");
		
		return new Time(
								Conversion.byteToUnsignedInt(data[0]),		// hour
								Conversion.byteToUnsignedInt(data[1]),		// minute
								Conversion.byteToUnsignedInt(data[2])		// second
							);

	}

	public static void relaysOneShot(int relayNo, int mode, int time) throws IOException
	{
		int errorCode = relaysOneShotN((byte) relayNo, (byte) mode, (short) time);
		
		if (E_NOERR != errorCode)
			throw new IOException(errorCode);
	}

	public static void setDate(int year, int month, int day, int weekday) throws IllegalArgumentException,  IOException
	{
		if ((year > 99 	|| year < 0) 		||
			 (month > 12 	|| month < 1) 		||
			 (day > 31 		|| day < 1) 		||
			 (weekday > 6  || weekday < 0)) 
			throw new IllegalArgumentException("Invalid Date"); 			
	
		int errorCode = setDateN((byte) year, (byte) month, (byte) day, (byte) weekday);
		
		if (E_NOERR != errorCode)
			throw new IOException(errorCode);
	}

	public static void setMultipleOutputs(int outMask, int blinkMask) throws IOException
	{
		int errorCode = setMultipleOutputsN((short) outMask, (short) blinkMask);
		
		if (E_NOERR != errorCode)
			throw new IOException(errorCode);
	}

	public static void setOutput(int outNo, int mode) throws IOException
	{
		int errorCode = setOutputN((byte) outNo, (byte) mode);
		
		if (E_NOERR != errorCode)
			throw new IOException(errorCode);
	}

	public static void setOutputBlinkFrequency(int period) throws IOException
	{
		int errorCode = setOutputBlinkFrequencyN((byte) period);
		
		if (E_NOERR != errorCode)
			throw new IOException(errorCode);
	}

	public static void setRelaysOnOffPWM(int relayNo, int mode) throws IOException
	{
		int errorCode = setRelaysOnOffPWMN((byte) relayNo, (byte) mode);
		
		if (E_NOERR != errorCode)
			throw new IOException(errorCode);
	}

	public static void setTime(int hour, int minute, int second) throws IllegalArgumentException,  IOException
	{
		if ((hour > 23 	|| hour < 0) 	||
			 (minute > 59 	|| minute < 0) ||
			 (second > 59  || second < 0)) 
			throw new IllegalArgumentException("Invalid Time");

		int errorCode = setTimeN((byte) hour, (byte) minute, (byte) second);
		
		if (E_NOERR != errorCode)
			throw new IOException(errorCode);
	}
	
	public static KeyboardEvent retrieveNextKeyboardEvent()
	{
		byte[] rawKeyEvent = new byte[2];

		if (retrieveNextKeyboardEventN(rawKeyEvent) > 0)
			return new KeyboardEvent(rawKeyEvent);
		else
			return null; 		
	}	
	
	public static void setChronometry(byte startEdge, 
												 byte stopEdge, 
												 byte stopCycles, 
												 byte inPin) throws IOException
	{
		int errorCode = setChronometryN(startEdge, stopEdge, stopCycles, inPin);
		
		if (errorCode != 0)
			throw new IOException(errorCode);
	}
		
	public static int getChronometryValue() throws IOException
	{
		int[] value = new int[2];
		int errorCode = getChronometryValueN(value);
		
		if (errorCode != 0)
			throw new IOException(errorCode);
		
		return value[0];
	}
		
	public static void setChronometryOnOff(byte onOff) throws IOException
	{
		int errorCode = setChronometryOnOffN(onOff);
		
		if (errorCode != 0)
			throw new IOException(errorCode);
	}	
		
	private static native int setChronometryN(byte startEdge, byte stopEdge, byte stopCycles, byte inPin);
	private static native int getChronometryValueN(int[] value);
	private static native int setChronometryOnOffN(byte onOff);	
	private static native int enableDisableCommunicationPortsN(byte portMask, short timeout);
	private static native int enableDisableKeyboardN(byte onOff);
	private static native int enableDisableKeyboardReportingN(byte onOff);	
	private static native int setRotaryEncoderTimeoutN(int value);
	private static native int enableDisableRotaryEncoderN(byte onOff);
	private static native int enableDisableRotaryEncoderReportingN(byte onOff);
	private static native int getRotaryEncoderValueN(byte[] value);	
	private static native int getADCValueN(byte port, byte[] response);
	private static native int getCurrentCommunicationPortN(byte[] response);
	private static native int getDateN(byte[] response);
	private static native int getEnabledCommunicationPortsN(byte[] response);
	private static native int getInputsStateN(byte[] response);
	private static native int getKeyboardStateN(int[] keyboardState);
	private static native int getTimeN(byte[] response);
	private static native int relaysOneShotN(byte relayNo, byte mode, short time);
	private static native int setDateN(byte year, byte month, byte day, byte weekday);
	private static native int setMultipleOutputsN(short outMask, short blinkMask);
	private static native int setOutputN(byte outNo, byte mode);
	private static native int setOutputBlinkFrequencyN(byte period);
	private static native int setPWM0N(int freq, short dutyCycle);
	private static native int setPWM1N(short dutyCycle);
	private static native int setRelaysOnOffPWMN(byte relayNo, byte mode);
	private static native int setTimeN(byte hour, byte minute, byte second);
	private static native int retrieveNextKeyboardEventN(byte[] response);
}
