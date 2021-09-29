#define JAVA_TAB_LOOP_START for (int i = 0; i < FJavaIDEFrame->JavaTabs.Count(); i++) \
	{ \
		TJavaTab *java_tab = FJavaIDEFrame->JavaTabs[i]; \
		if (java_tab == NULL) \
			throw Exception("java_tab == NULL"); \

#define JAVA_TAB_LOOP_END	}


bool TJavaProject::IsFileOpen(UnicodeString file_name)
{
	TJavaTab *java_tab;
	TLMDDockPanel *panel;

	if (file_name.IsEmpty())
		return false;

	JAVA_TAB_LOOP_START
		// this is done for every java tab
		if (java_tab->FileName == file_name)
			return true;
	JAVA_TAB_LOOP_END

	return false;
}
