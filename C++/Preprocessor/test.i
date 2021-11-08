 bool TJavaProject::IsFileOpen(UnicodeString file_name)
 {
  TJavaTab *java_tab;
  TLMDDockPanel *panel;
  if (file_name.IsEmpty())
   return false;
  for (int i = 0; i < FJavaIDEFrame->JavaTabs.Count(); i++) { TJavaTab *java_tab = FJavaIDEFrame->JavaTabs[i]; if (java_tab == NULL) throw Exception
 ("java_tab == NULL");()
   if (java_tab->FileName == file_name)
    return true;
  }
  return false;
 }
