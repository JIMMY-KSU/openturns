; 
; Common var and function definition for ot windows installer.
;

SetCompressor /SOLID lzma

RequestExecutionLevel user

; Prefix where openturns is installed on Linux.
!ifndef OPENTURNS_PREFIX
  !error "OPENTURNS_PREFIX must be defined"
!endif

!ifndef ARCH
  !error "ARCH must be defined"
!endif

!include "WordFunc.nsh" ; for ${WordAdd}, ${WordReplace}
!include "FileFunc.nsh" ; for ${DirState} , ${GetParent}, ${ConfigWrite}, ${GetFileAttributes}
!include "TextFunc.nsh" ; for ${ConfigRead}
!include "LogicLib.nsh" ; for ${If}

; Script generated by the HM NIS Edit Script Wizard.
; HM NIS Edit Wizard helper defines
!ifndef PRODUCT_VERSION
  !error "PRODUCT_VERSION must be defined"
!endif
!define PRODUCT_WEB_SITE "http://www.openturns.org"
!define PRODUCT_DIR_REGKEY "Software\OpenTURNS"
!define PRODUCT_INST_ROOT_KEY "HKLM"

; Where win specific things reside : examples, dedendancies installers and headers... (relative path)
!define WINDEPS openturns-developers-windeps-${PRODUCT_VERSION}


!macro CHECK_REG_VIEW
  ${If} "${ARCH}" == "x86_64"
     SetRegView 64
  ${EndIf}
!macroend


!macro PRINT MSG
  SetDetailsPrint both
  DetailPrint "${MSG}"
  SetDetailsPrint none
!macroend


Var UserInstall

; Check that current user has administrator privileges 
; if ok : set UserInstall to 0, if not : set UserInstall to 1
!macro CHECK_USER_INSTALL WARN_MSG
  StrCpy $UserInstall "0"

  ; avoid check if /userlevel option is present on command line
  ${GetParameters} $R1
  ClearErrors
  ${GetOptions} $R1 '/userlevel=' $R0
  IfErrors 0 set_level

  ClearErrors
  WriteRegStr ${PRODUCT_INST_ROOT_KEY} ${PRODUCT_DIR_REGKEY} "Test" "${PRODUCT_VERSION}"
  IfErrors user_install admin_install
  user_install:
  StrCpy $UserInstall "1"
  MessageBox MB_OK|MB_ICONINFORMATION "You are not running Windows from an administrator account.$\r$\rTo enable admin rights on Windows Vista and above: right click on the installer, choose 'Run as administrator'.$\r$\r${WARN_MSG}" /SD IDOK
  admin_install:
  DeleteRegValue ${PRODUCT_INST_ROOT_KEY} ${PRODUCT_DIR_REGKEY} "Test"
  Goto end_set_level

  set_level:
  StrCpy $UserInstall $R0
  end_set_level:
!macroend


!macro CHECK_USER_INSTALL_FILE FILE_NAME
  ; Get previous installation mode
  IfFileExists "${FILE_NAME}" user_mode 0
  StrCpy $UserInstall "0"
  Goto end_user_mode
  user_mode:
  StrCpy $UserInstall "1"
  end_user_mode:

  ${If} "$UserInstall" == "0"
    !insertmacro CHECK_USER_INSTALL "Uninstall from a non-administrator could not work cause you installed ${PRODUCT_NAME} from an admin account."
  ${EndIf}
!macroend


!macro CREATE_USER_INSTALL_FILE FILE_NAME
  ; create a file for uninstaller
  FileOpen $0 "${FILE_NAME}" w
  IfErrors userfile_fail
  FileWrite $0 "${PRODUCT_NAME} was installed in user mode."
  FileClose $0
  userfile_fail:
!macroend


; Set whether OpenTURNS shortcuts will be in every user menu or only in current user menu.
; CHECK_USER_INSTALL must have been called first
!macro SET_MENU_CONTEXT
  ${If} "$UserInstall" == "0"
    SetShellVarContext all
  ${Else}
    SetShellVarContext current
  ${EndIf}
!macroend



Var OT_INSTALL_PATH

!define Python_default_INSTALL_PATH "C:\Python${PYBASEVER_NODOT}"
!define Default_OT_INSTALL_PATH "${Python_default_INSTALL_PATH}\Lib\site-packages\openturns"


; get openturns version from the file VERSION.TXT
; need $R5 set to VERSION.txt path
; return in $R1 openturns version found
Function GetOpenTURNSFileVersion
  ClearErrors
  FileOpen $0 $R5 r
  IfErrors done
  FileRead $0 $1
  ${WordFind} $1 " " "+2" $R1
  FileClose $0
  done:
FunctionEnd


; return in $R0 openturns path found.
; return in $R1 openturns version found.
Function CheckOpenTURNS
  StrCpy $R0 ""
  StrCpy $R1 ""
  ClearErrors

  ; search the prog in registry
  ReadRegStr $R0 HKLM "${PRODUCT_DIR_REGKEY}" "InstallPath"
  ${If} "$R0" == ""
    !insertmacro PRINT "OpenTURNS not found in registry."
  ${Else}
    ; Check that the directory fetched in the registry is existing.
    IfFileExists "$R0\*.*" 0 openturns_reg_not_found
      !insertmacro PRINT "=> OpenTURNS found here: $R0."
      ReadRegStr $R1 HKLM "${PRODUCT_DIR_REGKEY}" "Current Version"
      ; version not found in registry rty with the version file
      ${If} $R1 == ""
        StrCpy $R5 "$R0\VERSION.TXT"
        Call GetOpenTURNSFileVersion
      ${EndIf}
    Goto end_openturns_reg_not_found
    openturns_reg_not_found:
      !insertmacro PRINT "OpenTURNS not found in $R0."
      StrCpy $R0 ""
    end_openturns_reg_not_found:
  ${EndIf}

  ; Search the prog in default directory
  ${If} $R0 == ""
    IfFileExists "${Default_OT_INSTALL_PATH}\*.*" 0 openturns_not_found
    !insertmacro PRINT "OpenTURNS found in ${Default_OT_INSTALL_PATH}."
    StrCpy $R0 "${Default_OT_INSTALL_PATH}"
    StrCpy $R5 "$R0\VERSION.TXT"
    Call GetOpenTURNSFileVersion
    openturns_not_found:
  ${EndIf}

FunctionEnd


