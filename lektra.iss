[Setup]
AppName=Lektra
AppVersion=0.6.9
DefaultDirName={autopf}\Lektra
DefaultGroupName=Lektra
OutputDir=installer
OutputBaseFilename=lektra-setup
ChangesAssociations=yes

[Registry]
; PDF
Root: HKCR; Subkey: ".pdf\OpenWithProgids";             ValueType: string; ValueName: "Lektra.pdf";  ValueData: ""; Flags: uninsdeletevalue
Root: HKCR; Subkey: "Lektra.pdf";                       ValueType: string; ValueName: "";             ValueData: "PDF Document";          Flags: uninsdeletekey
Root: HKCR; Subkey: "Lektra.pdf\DefaultIcon";           ValueType: string; ValueName: "";             ValueData: "{app}\lektra.exe,0"
Root: HKCR; Subkey: "Lektra.pdf\shell\open\command";    ValueType: string; ValueName: "";             ValueData: """{app}\lektra.exe"" ""%1"""

; DjVu
Root: HKCR; Subkey: ".djvu\OpenWithProgids";            ValueType: string; ValueName: "Lektra.djvu"; ValueData: ""; Flags: uninsdeletevalue
Root: HKCR; Subkey: "Lektra.djvu";                      ValueType: string; ValueName: "";             ValueData: "DjVu Document";         Flags: uninsdeletekey
Root: HKCR; Subkey: "Lektra.djvu\DefaultIcon";          ValueType: string; ValueName: "";             ValueData: "{app}\lektra.exe,0"
Root: HKCR; Subkey: "Lektra.djvu\shell\open\command";   ValueType: string; ValueName: "";             ValueData: """{app}\lektra.exe"" ""%1"""

; XPS / OXPS
Root: HKCR; Subkey: ".xps\OpenWithProgids";             ValueType: string; ValueName: "Lektra.xps";  ValueData: ""; Flags: uninsdeletevalue
Root: HKCR; Subkey: "Lektra.xps";                       ValueType: string; ValueName: "";             ValueData: "XPS Document";          Flags: uninsdeletekey
Root: HKCR; Subkey: "Lektra.xps\DefaultIcon";           ValueType: string; ValueName: "";             ValueData: "{app}\lektra.exe,0"
Root: HKCR; Subkey: "Lektra.xps\shell\open\command";    ValueType: string; ValueName: "";             ValueData: """{app}\lektra.exe"" ""%1"""

Root: HKCR; Subkey: ".oxps\OpenWithProgids";            ValueType: string; ValueName: "Lektra.oxps"; ValueData: ""; Flags: uninsdeletevalue
Root: HKCR; Subkey: "Lektra.oxps";                      ValueType: string; ValueName: "";             ValueData: "OXPS Document";         Flags: uninsdeletekey
Root: HKCR; Subkey: "Lektra.oxps\DefaultIcon";          ValueType: string; ValueName: "";             ValueData: "{app}\lektra.exe,0"
Root: HKCR; Subkey: "Lektra.oxps\shell\open\command";   ValueType: string; ValueName: "";             ValueData: """{app}\lektra.exe"" ""%1"""

; CBZ / CBT
Root: HKCR; Subkey: ".cbz\OpenWithProgids";             ValueType: string; ValueName: "Lektra.cbz";  ValueData: ""; Flags: uninsdeletevalue
Root: HKCR; Subkey: "Lektra.cbz";                       ValueType: string; ValueName: "";             ValueData: "CBZ Archive";           Flags: uninsdeletekey
Root: HKCR; Subkey: "Lektra.cbz\DefaultIcon";           ValueType: string; ValueName: "";             ValueData: "{app}\lektra.exe,0"
Root: HKCR; Subkey: "Lektra.cbz\shell\open\command";    ValueType: string; ValueName: "";             ValueData: """{app}\lektra.exe"" ""%1"""

Root: HKCR; Subkey: ".cbt\OpenWithProgids";             ValueType: string; ValueName: "Lektra.cbt";  ValueData: ""; Flags: uninsdeletevalue
Root: HKCR; Subkey: "Lektra.cbt";                       ValueType: string; ValueName: "";             ValueData: "CBT Archive";           Flags: uninsdeletekey
Root: HKCR; Subkey: "Lektra.cbt\DefaultIcon";           ValueType: string; ValueName: "";             ValueData: "{app}\lektra.exe,0"
Root: HKCR; Subkey: "Lektra.cbt\shell\open\command";    ValueType: string; ValueName: "";             ValueData: """{app}\lektra.exe"" ""%1"""

; EPUB
Root: HKCR; Subkey: ".epub\OpenWithProgids";            ValueType: string; ValueName: "Lektra.epub"; ValueData: ""; Flags: uninsdeletevalue
Root: HKCR; Subkey: "Lektra.epub";                      ValueType: string; ValueName: "";             ValueData: "EPUB Document";         Flags: uninsdeletekey
Root: HKCR; Subkey: "Lektra.epub\DefaultIcon";          ValueType: string; ValueName: "";             ValueData: "{app}\lektra.exe,0"
Root: HKCR; Subkey: "Lektra.epub\shell\open\command";   ValueType: string; ValueName: "";             ValueData: """{app}\lektra.exe"" ""%1"""

; FB2
Root: HKCR; Subkey: ".fb2\OpenWithProgids";             ValueType: string; ValueName: "Lektra.fb2";  ValueData: ""; Flags: uninsdeletevalue
Root: HKCR; Subkey: "Lektra.fb2";                       ValueType: string; ValueName: "";             ValueData: "FictionBook Document";  Flags: uninsdeletekey
Root: HKCR; Subkey: "Lektra.fb2\DefaultIcon";           ValueType: string; ValueName: "";             ValueData: "{app}\lektra.exe,0"
Root: HKCR; Subkey: "Lektra.fb2\shell\open\command";    ValueType: string; ValueName: "";             ValueData: """{app}\lektra.exe"" ""%1"""

; MOBI
Root: HKCR; Subkey: ".mobi\OpenWithProgids";            ValueType: string; ValueName: "Lektra.mobi"; ValueData: ""; Flags: uninsdeletevalue
Root: HKCR; Subkey: "Lektra.mobi";                      ValueType: string; ValueName: "";             ValueData: "Mobipocket eBook";      Flags: uninsdeletekey
Root: HKCR; Subkey: "Lektra.mobi\DefaultIcon";          ValueType: string; ValueName: "";             ValueData: "{app}\lektra.exe,0"
Root: HKCR; Subkey: "Lektra.mobi\shell\open\command";   ValueType: string; ValueName: "";             ValueData: """{app}\lektra.exe"" ""%1"""

; JPEG
Root: HKCR; Subkey: ".jpg\OpenWithProgids";             ValueType: string; ValueName: "Lektra.jpg";  ValueData: ""; Flags: uninsdeletevalue
Root: HKCR; Subkey: "Lektra.jpg";                       ValueType: string; ValueName: "";             ValueData: "JPEG Image";            Flags: uninsdeletekey
Root: HKCR; Subkey: "Lektra.jpg\DefaultIcon";           ValueType: string; ValueName: "";             ValueData: "{app}\lektra.exe,0"
Root: HKCR; Subkey: "Lektra.jpg\shell\open\command";    ValueType: string; ValueName: "";             ValueData: """{app}\lektra.exe"" ""%1"""

Root: HKCR; Subkey: ".jpeg\OpenWithProgids";            ValueType: string; ValueName: "Lektra.jpeg"; ValueData: ""; Flags: uninsdeletevalue
Root: HKCR; Subkey: "Lektra.jpeg";                      ValueType: string; ValueName: "";             ValueData: "JPEG Image";            Flags: uninsdeletekey
Root: HKCR; Subkey: "Lektra.jpeg\DefaultIcon";          ValueType: string; ValueName: "";             ValueData: "{app}\lektra.exe,0"
Root: HKCR; Subkey: "Lektra.jpeg\shell\open\command";   ValueType: string; ValueName: "";             ValueData: """{app}\lektra.exe"" ""%1"""

; PNG
Root: HKCR; Subkey: ".png\OpenWithProgids";             ValueType: string; ValueName: "Lektra.png";  ValueData: ""; Flags: uninsdeletevalue
Root: HKCR; Subkey: "Lektra.png";                       ValueType: string; ValueName: "";             ValueData: "PNG Image";             Flags: uninsdeletekey
Root: HKCR; Subkey: "Lektra.png\DefaultIcon";           ValueType: string; ValueName: "";             ValueData: "{app}\lektra.exe,0"
Root: HKCR; Subkey: "Lektra.png\shell\open\command";    ValueType: string; ValueName: "";             ValueData: """{app}\lektra.exe"" ""%1"""

; TIFF
Root: HKCR; Subkey: ".tif\OpenWithProgids";             ValueType: string; ValueName: "Lektra.tif";  ValueData: ""; Flags: uninsdeletevalue
Root: HKCR; Subkey: "Lektra.tif";                       ValueType: string; ValueName: "";             ValueData: "TIFF Image";            Flags: uninsdeletekey
Root: HKCR; Subkey: "Lektra.tif\DefaultIcon";           ValueType: string; ValueName: "";             ValueData: "{app}\lektra.exe,0"
Root: HKCR; Subkey: "Lektra.tif\shell\open\command";    ValueType: string; ValueName: "";             ValueData: """{app}\lektra.exe"" ""%1"""

Root: HKCR; Subkey: ".tiff\OpenWithProgids";            ValueType: string; ValueName: "Lektra.tiff"; ValueData: ""; Flags: uninsdeletevalue
Root: HKCR; Subkey: "Lektra.tiff";                      ValueType: string; ValueName: "";             ValueData: "TIFF Image";            Flags: uninsdeletekey
Root: HKCR; Subkey: "Lektra.tiff\DefaultIcon";          ValueType: string; ValueName: "";             ValueData: "{app}\lektra.exe,0"
Root: HKCR; Subkey: "Lektra.tiff\shell\open\command";   ValueType: string; ValueName: "";             ValueData: """{app}\lektra.exe"" ""%1"""

; SVG
Root: HKCR; Subkey: ".svg\OpenWithProgids";             ValueType: string; ValueName: "Lektra.svg";  ValueData: ""; Flags: uninsdeletevalue
Root: HKCR; Subkey: "Lektra.svg";                       ValueType: string; ValueName: "";             ValueData: "SVG Image";             Flags: uninsdeletekey
Root: HKCR; Subkey: "Lektra.svg\DefaultIcon";           ValueType: string; ValueName: "";             ValueData: "{app}\lektra.exe,0"
Root: HKCR; Subkey: "Lektra.svg\shell\open\command";    ValueType: string; ValueName: "";             ValueData: """{app}\lektra.exe"" ""%1"""

[Files]
Source: ".\build\release\*"; DestDir: "{app}"; Flags: recursesubdirs
Source: ".\tutorial.pdf";     DestDir: "{userappdata}\Lektra";  Flags: ignoreversion

[Icons]
Name: "{group}\Lektra"; Filename: "{app}\lektra.exe"
Name: "{commondesktop}\Lektra"; Filename: "{app}\lektra.exe"

[Run]
Filename: "{app}\lektra.exe"; Description: "Launch Lektra"; Flags: postinstall
