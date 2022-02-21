#include "CommonLib.h"
#pragma hdrstop

//#pragma package(smart_init)

//---------------------------------------------------------------------------
TRealString::TRealString()
{
  Create("", 0);
  FReferenceCount = 1;
}

//---------------------------------------------------------------------------
TRealString::TRealString(const TRealString &RealString)
{
  Create(RealString.FArray, RealString.FLength);
  FReferenceCount = 1;
}

//---------------------------------------------------------------------------
TRealString::TRealString(const char *Text, int Length)
{
  Create(Text, Length);
  FReferenceCount = 1;
}

//---------------------------------------------------------------------------
TRealString::TRealString(int Length, int FillChr)
{
  FArrayLength = BlockLength(Length);
  FArray = new char[FArrayLength];
  memset(FArray, FillChr, Length);
  FArray[Length] = 0;
  FLength = Length;
  FReferenceCount = 1;
}

//---------------------------------------------------------------------------
TRealString::~TRealString() {}

//---------------------------------------------------------------------------
void TRealString::Create(const char *Text, int Length)
{
  FArrayLength = BlockLength(Length);
  FArray = new char[FArrayLength];
  memcpy(FArray, Text, Length);
  FArray[Length] = 0;
  FLength = Length;
}

//---------------------------------------------------------------------------
void TRealString::PreAllocate(int Length)
{
  FArray.Destroy();
  FArrayLength = BlockLength(Length);
  FArray = new char[FArrayLength];
  memset(FArray, ' ', Length);
  FArray[Length] = 0;
  FLength = Length;
}

//---------------------------------------------------------------------------
void TRealString::AppendCharacter(int Character)
{
  // Compare & allow for terminating zero
  if(FLength + 1 >= FArrayLength) {
    // Text array grows by double
    FArrayLength = _max(BlockLength(FLength + 1), FArrayLength << 1);
    FArray = (char*)realloc(FArray, FArrayLength);
    if(!FArray)
      throw Exception("Out of memory");
  }

  FArray[FLength++] = (char)Character;
  FArray[FLength] = 0;
}

//---------------------------------------------------------------------------
void TRealString::Insert(const char *Text, int Length, int Position)
{
  int NewLength = ((Position > FLength) ? Position : FLength) + Length;

  // Compare & allow for terminating zero
  if(NewLength >= FArrayLength) {
    // Text array grows by double
    FArrayLength = _max(BlockLength(NewLength), FArrayLength << 1);
    FArray = (char*)realloc(FArray, FArrayLength);
    if(!FArray)
      throw Exception("Out of memory");
  }

  // Make room for new text
  if(Position < FLength)
    memmove(FArray + Position + Length, FArray + Position, FLength - Position);
  // Set blank from end of existing text to position (if inserting past end of existing string)
  else if(Position > FLength)
    memset(FArray + FLength, ' ', Position - FLength);

  // Copy new text
  memcpy(FArray + Position, Text, Length);

  // Set NULL terminator
  FLength = NewLength;
  FArray[FLength] = 0;
}

//---------------------------------------------------------------------------
void TRealString::Replace(const char *Text, int Length, int Position)
{
  int NewLength = _max(FLength, Position + Length);

  // Compare & allow for terminating zero
  if(NewLength >= FArrayLength) {
    // Text array grows by double
		FArrayLength = _max(BlockLength(NewLength), FArrayLength << 1);
    FArray = (char*)realloc(FArray, FArrayLength);
    if(!FArray)
      throw Exception("Out of memory");
  }

  // Set blank from end of existing text to position (if inserting past end of existing string)
  if(Position > FLength)
    memset(FArray + FLength, ' ', Position - FLength);

  // Copy new text
  memcpy(FArray + Position, Text, Length);

  // Set NULL terminator
  FLength = NewLength;
  FArray[FLength] = 0;
}

//---------------------------------------------------------------------------
void TRealString::Remove(int Position, int Length)
{
  if(Position >= FLength)
    return;

  Length = _min(Length, FLength - Position);
  int EndOfTextToRemove = Position + Length;
  int NewLength = FLength - Length;

  memmove(FArray + Position, FArray + EndOfTextToRemove, FLength - EndOfTextToRemove);
  FLength = NewLength;
  FArray[FLength] = 0;

  // Compare & allow for terminating zero
  // Text array grows/shrinks by double/half
  if(FLength < (FArrayLength >> 1) - szHysteresis) {
    FArrayLength = BlockLength(FLength);
    FArray = (char*)realloc(FArray, FArrayLength);
    if(!FArray)
      throw Exception("Out of memory");
  }
}


