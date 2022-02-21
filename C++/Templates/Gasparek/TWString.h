#ifndef TWStringH
#define TWStringH

class WString
{
private:
	UnicodeString FText;

public:
	WString() : FText("") {  }
	WString(int IntVal);
	WString(int Length, wchar_t Filler);
	WString(const wchar_t *Str) : FText(Str) {  }
	WString(const char *Str) : FText(Str) {  }
	WString(const AnsiString &Str) : FText(Str) {  }
	WString(const UnicodeString &Str) : FText(Str) {  }

	void SetLength(int MaxLength) { FText.SetLength(MaxLength); }
	void LimitLength(int MaxLength) { SetLength(MaxLength); }
	int Length() const { return FText.Length(); }
	void RLTrim() { FText = FText.Trim(); }
	void LTrim() { FText = FText.TrimLeft(); }
	void RTrim() { FText = FText.TrimRight(); }
	WString Trim(bool New = false);
	WString TrimRight(bool New = false);
	WString TrimLeft(bool New = false);
	bool IsEmpty() const { return FText.IsEmpty(); }
	bool IsBlank() const { return FText.IsEmpty(); }
	int Pos(const UnicodeString &Text) const { return FText.Pos(Text) - 1; }
	int Find(const UnicodeString &Text) const { return Pos(Text); }
	int FindI(const UnicodeString &Text) const;
	int Find(int Chr) const;
	WString SubString(int Start, int Length) const { return FText.SubString(Start+1, Length); }
	WString Mid(int Start, int Length) const { return SubString(Start, Length); }
 	WString Left(int Length) const { return FText.SubString(1, _min(FText.Length(), Length)); }
 	//JH: WString Right(int Length) const { return FText.SubString(_min(1, FText.Length() - Length), _max(1, FText.Length() - Length)); }
   WString Right(int Length) const { return FText.SubString(_max(1, FText.Length() - Length + 1), _min(Length, FText.Length()));}
	UnicodeString Text() const { return FText; }
	void Insert(const UnicodeString& Str, int Index) { FText.Insert(Str, Index+1); }
	void Remove(int Index, int Length) { FText.Delete(Index+1, Length); }
	void Remove(char Char);
	void Remove(const wchar_t *AnyChar);

	int ToInt() const { return FText.ToInt(); }
	double ToDouble() const { return FText.ToDouble(); }
	wchar_t *c_str() const { return FText.c_str(); }
	WString &sprintf(const wchar_t* format, ...);

	int Compare(const UnicodeString& Other) const { return FText.Compare(Other); }
	int CompareIC(const UnicodeString& Other) const { return FText.CompareIC(Other); }
	bool Equals(const WString &Other, bool IgnoreCase = true) const
		{ return IgnoreCase ? (FText.CompareIC(Other.Text()) == 0) : (FText.Compare(Other.Text()) == 0); }

	WString UpperCase(bool New = false);
	WString LowerCase(bool New = false);
	void ToUpper() { FText = FText.UpperCase(); }
	void ToLower() { FText = FText.LowerCase(); }

	WString operator +(const WString& Other) const;
	void operator +=(const WString& Other) { FText += Other.FText; }
	void operator +=(const UnicodeString& Other) { FText += Other; }
	void operator +=(const char *Other) { FText += Other; }
	void operator +=(const wchar_t Other) { FText += Other; }
	void operator =(const WString& Other) { FText = Other.FText; }
	void operator =(const UnicodeString& Other) { FText = Other; }
	void operator =(const char *Other) { FText = Other; }
	void operator =(const wchar_t *Other) { FText = Other; }
	bool operator < (const WString& Other) const { return FText < Other.FText; }
	bool operator <=(const WString& Other) const { return FText <= Other.FText; }
	bool operator >(const WString& Other) const { return FText > Other.FText; }
	bool operator >=(const WString& Other) const { return FText >= Other.FText; }
	bool operator ==(const WString& Other) const { return FText == Other.FText; }
	bool operator !=(const WString& Other) const { return FText != Other.FText; }
	WideChar operator [](const int Index) const { return FText[Index + 1]; }
	WideChar& operator [](const int Index) { return FText[Index + 1]; }

	int Words (int Separator, bool IgnoreQuotes = false) const;
	WString Word (int WordNo, int Separator, bool IgnoreQuotes = false) const;

	int Count(int Char) const;

	void Replace(wchar_t Old, wchar_t New);

};


#endif
