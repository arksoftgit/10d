DROP TABLE ACCESSAUTHORITY ;
DROP TABLE z_ACTION ;
DROP TABLE ADW_INFOTYPE ;
DROP TABLE APPLICATION ;
DROP TABLE AUDITTRAIL ;
DROP TABLE AUDITTRAILMETA ;
DROP TABLE BUFFER ;
DROP TABLE COLOR ;
DROP TABLE COLORDEF ;
DROP TABLE COLOROVERRIDE ;
DROP TABLE CONTEXT ;
DROP TABLE CONTROL ;
DROP TABLE CONTROLDEF ;
DROP TABLE CPL ;
DROP TABLE CPL_REUSEABLEITEM ;
DROP TABLE CPLR ;
DROP TABLE CPLR_ENQUEUE ;
DROP TABLE DEFINEDITEM ;
DROP TABLE DELIVERYENVPKG ;
DROP TABLE DIALOG ;
DROP TABLE z_DOMAIN ;
DROP TABLE ENTPER_MODEL ;
DROP TABLE ER_ATTRIBUTE ;
DROP TABLE ER_ENTIDENTIFIER ;
DROP TABLE ER_ENTITY ;
DROP TABLE ER_FACTTYPE ;
DROP TABLE ER_RELLINK ;
DROP TABLE ER_RELTYPE ;
DROP TABLE EVENT ;
DROP TABLE EVENTDEF ;
DROP TABLE EXECCOMPOSITE ;
DROP TABLE z_FILE ;
DROP TABLE FONT ;
DROP TABLE FONTDEF ;
DROP TABLE FONTOVERRIDE ;
DROP TABLE z_GROUP ;
DROP TABLE GROUPSET ;
DROP TABLE HEADERFILE ;
DROP TABLE HOTKEY ;
DROP TABLE INSTALLATION ;
DROP TABLE LOD ;
DROP TABLE LOD_ATTRIBUTE ;
DROP TABLE LOD_ENTITY ;
DROP TABLE LPLR ;
DROP TABLE MAPDEF ;
DROP TABLE MAPREF ;
DROP TABLE MENU ;
DROP TABLE NLS_TEXT ;
DROP TABLE OPERATION ;
DROP TABLE z_OPTION ;
DROP TABLE ORIGSIRONFIELD ;
DROP TABLE PAGE ;
DROP TABLE PARAMETER ;
DROP TABLE PHYSOVERRIDE ;
DROP TABLE POD ;
DROP TABLE POD_ATTRIBUTE ;
DROP TABLE POD_ENTITY ;
DROP TABLE POD_ENTITYMAPFLD ;
DROP TABLE POD_ENTITYMAPREC ;
DROP TABLE POD_RELLINKMAPFLD ;
DROP TABLE POD_RELLINKMAPREC ;
DROP TABLE PRESENVDEF ;
DROP TABLE PROPERTYDEF ;
DROP TABLE REGULAREXPRESSION ;
DROP TABLE REPORT ;
DROP TABLE REPOSITORYCLIENT ;
DROP TABLE REVEVENT ;
DROP TABLE REVSUBEVENT ;
DROP TABLE SA_ENTITY ;
DROP TABLE SA_RELTYPE ;
DROP TABLE SIRONCOMMENT ;
DROP TABLE SIRONKATALOG ;
DROP TABLE SOURCEFILE ;
DROP TABLE SUBJECTAREA ;
DROP TABLE SYSENQUEUE ;
DROP TABLE TABLEENTRY ;
DROP TABLE TE_DB_ENVIRON ;
DROP TABLE TE_DBMS_SOURCE ;
DROP TABLE TE_FIELDDATAREL ;
DROP TABLE TE_PHYSICALDATATYPE ;
DROP TABLE TE_TABLRECDATAREL ;
DROP TABLE TE_TABLRECKEY ;
DROP TABLE UI_SPEC ;
DROP TABLE UIS_ENTITY ;
DROP TABLE UIS_INCLUDE ;
DROP TABLE UIS_QUALLIST ;
DROP TABLE UIS_TAB ;
DROP TABLE z_USER ;
DROP TABLE USERMETASTATUS ;
DROP TABLE VIEWOBJREF ;
DROP TABLE WINDOW ;
DROP TABLE WINDOWSTYLE ;
DROP TABLE WNDDESIGNSPEC ;
DROP TABLE WNDEVENT ;
DROP TABLE Z_METADEF ;
DROP TABLE MM_UIS_TAB_FOR_LOD_ATTRIBUTE ;
DROP TABLE MMTETABLRECDATARELSDNTEDBENVIR ;
DROP TABLE MM_VIEWOBJREF_FOR_REPORT ;
DROP TABLE MMAPPLICATIONSXCTBLBYREPOSITOR ;
DROP TABLE MM_UI_SPEC_HAS_VIEWOBJREF ;
DROP TABLE MM_CONTROLDEF_HASMSSG_OPERATIO ;
DROP TABLE MM_TE_TABLRECKEYSTEFIELDDATARE ;
DROP TABLE MMCONTROLDEF4CPTSCHNGFRMCONTRO ;
DROP TABLE MMCONTROLDEF1CPTSPRNTCONTROLDE ;
DROP TABLE MMCONTROLDEF2CPTSCHLDCONTROLDE ;
DROP TABLE MM_SA_ENTITY_SNVLVDNSUBJECTARE ;
DROP TABLE MMTETABLRECDATARELMPLMNTSERENT ;
DROP TABLE MMTEPHYSICALDATATYPECNMPLMNTZD ;
DROP TABLE MM_SA_RELTYPESNVLVDNSUBJECTARE ;
DROP TABLE MM_UIS_ENTITY_HSMNTLODATTRIBUT ;
DROP TABLE MM_UIS_ENTITY_HSLSTLODATTRIBUT ;
DROP TABLE MMTEPHYSICALDATATYPESVLBLFRTED ;
DROP TABLE MM_Z_USER_BELONGTO_INSTALLATIO ;
DROP TABLE MM_REPOSITORYCLIENT_HAS_Z_USER ;
DROP TABLE MM_CPLR_ISREUSEDBY_CPLR ;
DROP TABLE MM_DIALOG_HAS_VIEWOBJREF ;
DROP TABLE MM_EXECCOMPOSITESGRPNGFZMETADE ;
DROP TABLE MMDIALOGCNTNSPTNCPLREUSEABLEIT ;
DROP TABLE MMDIALOGCNTNSWNDWCPLREUSEABLEI ;
DROP TABLE MMDIALOGCNTNSGRPCPLREUSEABLEIT ;
DROP TABLE MM_Z_ACTION_ACTIVATES_WINDOW ;

-- Entity - AccessAuthority 
CREATE TABLE ACCESSAUTHORITY ( 
           ZKEY               INTEGER            NOT NULL , 
           AUTHORITY          INTEGER            NOT NULL , 
           FK_ZKEY_Z_USER     INTEGER            NOT NULL , 
           FK_ZKEY_CPLR       INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX ACCESSAUTHORITYIDACCESSAUTHORT 
       ON ACCESSAUTHORITY ( 
           ZKEY ) ;
 
CREATE INDEX ACCESSAUTHORITY_FK_ZKEY_ZUSE01 
       ON ACCESSAUTHORITY ( 
           FK_ZKEY_Z_USER ) ;
 
CREATE INDEX ACCESSAUTHORITY_FK_ZKEY_CPLR02 
       ON ACCESSAUTHORITY ( 
           FK_ZKEY_CPLR ) ;
 
-- Entity - Action 
CREATE TABLE z_ACTION ( 
           TAG                TEXT( 32 )                  , 
           SB_SUBACTION       INTEGER                     , 
           SB_NEXTPREV        INTEGER                     , 
           SB_DELETENULL      INTEGER                     , 
           SB_ACTIONDISABLING INTEGER                     , 
           NOMAP              TEXT( 1 )                   , 
           TYPE               INTEGER            NOT NULL , 
           ACTIONTYPEASSCTDTX TEXT( 254 )                 , 
           TYPEDATA           TEXT( 32 )                  , 
           ZKEY               INTEGER            NOT NULL , 
           DIALOGNAME         TEXT( 32 )                  , 
           WINDOWNAME         TEXT( 32 )                  , 
           OPERCTRL           INTEGER                     , 
           POPUPMENUNAME      TEXT( 32 )                  , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_OPERATION  INTEGER                     , 
           FK_ZKEY_WINDOW     INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX z_ACTION_ID_ACTION 
       ON z_ACTION ( 
           ZKEY ) ;
 
CREATE INDEX z_ACTION_FK_ZKEY_OPERATION01 
       ON z_ACTION ( 
           FK_ZKEY_OPERATION ) ;
 
CREATE INDEX z_ACTION_FK_ZKEY_WINDOW02 
       ON z_ACTION ( 
           FK_ZKEY_WINDOW ) ;
 
-- Entity - ADW_InfoType 
CREATE TABLE ADW_INFOTYPE ( 
           NAME               TEXT( 32 )         NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           ER_EP_TOKN         INTEGER            NOT NULL , 
           TYPE               TEXT( 1 )          NOT NULL , 
           INTERNALLTH        INTEGER                     , 
           EXTERNALLTH        INTEGER                     , 
           DECIMALLTH         INTEGER                      ) ;
 
CREATE UNIQUE INDEX ADW_INFOTYPE_ID_ADW_INFOTYPE 
       ON ADW_INFOTYPE ( 
           ZKEY ) ;
 
-- Entity - Application 
CREATE TABLE APPLICATION ( 
           ZKEY               INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX APPLICATION_ID_APPLICATION 
       ON APPLICATION ( 
           ZKEY ) ;
 
-- Entity - AuditTrail 
CREATE TABLE AUDITTRAIL ( 
           USERNAME           TEXT( 32 )                  , 
           USERDESC           MEMO                        , 
           WKS_ID             INTEGER                     , 
           z_TIMESTAMP        TEXT( 25 )         NOT NULL , 
           SHORTDESC          TEXT( 254 )                 , 
           z_DESC             MEMO                        , 
           FK_TYPE_REVEVENT   INTEGER                     , 
           FKZKEYREPOSITORYCL INTEGER                     , 
           FKSUBTYPEREVSUBEVE INTEGER                     , 
           FKTYPEREVEVENTREVS INTEGER                     , 
           FK_ZKEY_CPLR       INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX AUDITTRAIL_ID 
       ON AUDITTRAIL ( 
           z_TIMESTAMP, 
           FK_ZKEY_CPLR ) ;
 
CREATE INDEX AUDITTRAIL_FK_TYPE_REVEVENT01 
       ON AUDITTRAIL ( 
           FK_TYPE_REVEVENT ) ;
 
CREATE INDEX AUDITTRAIL_FKZKEYREPOSITORYC02 
       ON AUDITTRAIL ( 
           FKZKEYREPOSITORYCL ) ;
 
CREATE INDEX AUDITTRAIL_FKSUBTYPEREVSUBEV03 
       ON AUDITTRAIL ( 
           FKSUBTYPEREVSUBEVE ) ;
 
CREATE INDEX AUDITTRAIL_FKTYPEREVEVENTREV04 
       ON AUDITTRAIL ( 
           FKTYPEREVEVENTREVS ) ;
 
CREATE INDEX AUDITTRAIL_FK_ZKEY_CPLR05 
       ON AUDITTRAIL ( 
           FK_ZKEY_CPLR ) ;
 
-- Entity - AuditTrailMeta 
CREATE TABLE AUDITTRAILMETA ( 
           BDELETED           TEXT( 1 )                   , 
           METADEFNAME        TEXT( 32 )         NOT NULL , 
           METADEFTYPE        INTEGER            NOT NULL , 
           FK_ZKEY_Z_METADEF  INTEGER                     , 
           FKZTIMESTAMPAUDITT TEXT( 25 )         NOT NULL , 
           FKZKEYCPLRAUDITTRA INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX AUDITTRAILMETA_ID 
       ON AUDITTRAILMETA ( 
           FKZKEYCPLRAUDITTRA, 
           FKZTIMESTAMPAUDITT, 
           METADEFNAME, 
           METADEFTYPE ) ;
 
CREATE INDEX AUDITTRAILMETA_FKZKEYZMETADE01 
       ON AUDITTRAILMETA ( 
           FK_ZKEY_Z_METADEF ) ;
 
CREATE INDEX AUDITTRAILMETAFKZTIMESTAMPDT02 
       ON AUDITTRAILMETA ( 
           FKZTIMESTAMPAUDITT ) ;
 
CREATE INDEX AUDITTRAILMETAFKZKEYCPLRADTT03 
       ON AUDITTRAILMETA ( 
           FKZKEYCPLRAUDITTRA ) ;
 
-- Entity - Buffer 
CREATE TABLE BUFFER ( 
           ZKEY               INTEGER            NOT NULL , 
           z_VALUE            LONGBINARY                  , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_Z_FILE     INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX BUFFER_ID_BUFFER 
       ON BUFFER ( 
           ZKEY ) ;
 
CREATE INDEX BUFFER_FK_ZKEY_Z_FILE01 
       ON BUFFER ( 
           FK_ZKEY_Z_FILE ) ;
 
-- Entity - Color 
CREATE TABLE COLOR ( 
           ZKEY               INTEGER            NOT NULL , 
           CUSTOMCOLORS       LONGBINARY                  , 
           TAG                TEXT( 32 )                  , 
           RGB_COLOR          INTEGER                     , 
           FK_ZKEY_PRESENVDEF INTEGER                      ) ;
 
CREATE UNIQUE INDEX COLOR_ZKEY 
       ON COLOR ( 
           ZKEY ) ;
 
CREATE INDEX COLOR_FK_ZKEY_PRESENVDEF01 
       ON COLOR ( 
           FK_ZKEY_PRESENVDEF ) ;
 
-- Entity - ColorDef 
CREATE TABLE COLORDEF ( 
           ZKEY               INTEGER            NOT NULL , 
           TAG                TEXT( 32 )         NOT NULL , 
           SEQNO              INTEGER                     , 
           FK_ZKEY_COLOR      INTEGER            NOT NULL , 
           FK_ZKEY_WINDOWSTYL INTEGER                     , 
           FK_ZKEY_CONTROLDEF INTEGER                      ) ;
 
CREATE UNIQUE INDEX COLORDEF_ZKEY 
       ON COLORDEF ( 
           ZKEY ) ;
 
CREATE INDEX COLORDEF_FK_ZKEY_COLOR01 
       ON COLORDEF ( 
           FK_ZKEY_COLOR ) ;
 
CREATE INDEX COLORDEF_FK_ZKEY_WINDOWSTYL02 
       ON COLORDEF ( 
           FK_ZKEY_WINDOWSTYL ) ;
 
CREATE INDEX COLORDEF_FK_ZKEY_CONTROLDEF03 
       ON COLORDEF ( 
           FK_ZKEY_CONTROLDEF ) ;
 
-- Entity - ColorOverride 
CREATE TABLE COLOROVERRIDE ( 
           ZKEY               INTEGER            NOT NULL , 
           SEQNO_DLGCTRL      INTEGER                     , 
           SEQNO_DLGWND       INTEGER                     , 
           FK_ZKEY_CONTROL    INTEGER                     , 
           FK_ZKEY_COLORDEF   INTEGER                     , 
           FK_ZKEY_COLOR      INTEGER                     , 
           FK_ZKEY_WINDOW     INTEGER                      ) ;
 
CREATE UNIQUE INDEX COLOROVERRIDE_ZKEY 
       ON COLOROVERRIDE ( 
           ZKEY ) ;
 
CREATE INDEX COLOROVERRIDE_FK_ZKEY_CONTRO01 
       ON COLOROVERRIDE ( 
           FK_ZKEY_CONTROL ) ;
 
CREATE INDEX COLOROVERRIDE_FK_ZKEYCOLORDE02 
       ON COLOROVERRIDE ( 
           FK_ZKEY_COLORDEF ) ;
 
CREATE INDEX COLOROVERRIDE_FK_ZKEY_COLOR03 
       ON COLOROVERRIDE ( 
           FK_ZKEY_COLOR ) ;
 
CREATE INDEX COLOROVERRIDE_FK_ZKEY_WINDOW04 
       ON COLOROVERRIDE ( 
           FK_ZKEY_WINDOW ) ;
 
-- Entity - Context 
CREATE TABLE CONTEXT ( 
           ZKEY               INTEGER            NOT NULL , 
           z_DESC             MEMO                        , 
           NAME               TEXT( 32 )                  , 
           DECIMALFORMAT      INTEGER                     , 
           EDITSTRING         TEXT( 254 )                 , 
           ISDEFAULT          TEXT( 1 )                   , 
           DIL_TEXT           TEXT( 254 )                 , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_Z_DOMAIN   INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX CONTEXT_ID_CONTEXT 
       ON CONTEXT ( 
           ZKEY ) ;
 
CREATE INDEX CONTEXT_FK_ZKEY_Z_DOMAIN01 
       ON CONTEXT ( 
           FK_ZKEY_Z_DOMAIN ) ;
 
-- Entity - Control 
CREATE TABLE CONTROL ( 
           TAG                TEXT( 32 )                  , 
           z_TEXT             TEXT( 254 )                 , 
           ZKEY               INTEGER            NOT NULL , 
           TYPE               INTEGER                     , 
           SUBTYPE            INTEGER                     , 
           DD_TARGETKEY       TEXT( 32 )                  , 
           DD_SOURCEKEY       TEXT( 32 )                  , 
           OPTIONFLAGS        INTEGER                     , 
           DD_TYPE            TEXT( 1 )                   , 
           IDNBR              INTEGER                     , 
           PSDLG_X            INTEGER                     , 
           PSDLG_Y            INTEGER                     , 
           SZDLG_X            INTEGER                     , 
           SZDLG_Y            INTEGER                     , 
           CTRLBOI            LONGBINARY                  , 
           UNDERLINE          INTEGER                     , 
           SYNCKEY            INTEGER                     , 
           DIL_TEXT           TEXT( 254 )                 , 
           REPORTGROUPTYPE    TEXT( 2 )                   , 
           FORCEHEADERPERENTT TEXT( 1 )                   , 
           EXTENDEDSTYLE      INTEGER                     , 
           z_GUID             TEXT( 64 )                  , 
           PROPERTIES         LONGBINARY                  , 
           AUTOSEQ            INTEGER                     , 
           AUTOSEQ02          INTEGER                     , 
           AUTOSEQ03          INTEGER                     , 
           FK_ZKEY_Z_GROUP    INTEGER                     , 
           FK_ZKEYPHYSOVERRID INTEGER                     , 
           FK_ZKEY_CONTROLDEF INTEGER                     , 
           FK_ZKEY_CONTROL    INTEGER                     , 
           FK_ZKEY_MENU       INTEGER                     , 
           FK_ZKEY_WINDOW     INTEGER                     , 
           FK_ZKEY_CONTROL02  INTEGER                      ) ;
 
CREATE UNIQUE INDEX CONTROL_ID_CONTROL 
       ON CONTROL ( 
           ZKEY ) ;
 
CREATE INDEX CONTROL_FK_ZKEY_Z_GROUP01 
       ON CONTROL ( 
           FK_ZKEY_Z_GROUP ) ;
 
CREATE INDEX CONTROL_FK_ZKEYPHYSOVERRID02 
       ON CONTROL ( 
           FK_ZKEYPHYSOVERRID ) ;
 
CREATE INDEX CONTROL_FK_ZKEY_CONTROLDEF03 
       ON CONTROL ( 
           FK_ZKEY_CONTROLDEF ) ;
 
CREATE INDEX CONTROL_FK_ZKEY_CONTROL04 
       ON CONTROL ( 
           FK_ZKEY_CONTROL ) ;
 
CREATE INDEX CONTROL_FK_ZKEY_MENU05 
       ON CONTROL ( 
           FK_ZKEY_MENU ) ;
 
CREATE INDEX CONTROL_FK_ZKEY_WINDOW06 
       ON CONTROL ( 
           FK_ZKEY_WINDOW ) ;
 
CREATE INDEX CONTROL_FK_ZKEY_CONTROL0207 
       ON CONTROL ( 
           FK_ZKEY_CONTROL02 ) ;
 
-- Entity - ControlDef 
CREATE TABLE CONTROLDEF ( 
           ZKEY               INTEGER            NOT NULL , 
           LASTSYNCDATE       TEXT( 25 )                  , 
           z_DESC             MEMO                        , 
           TAG                TEXT( 32 )                  , 
           ID                 INTEGER                     , 
           RT_DLL_NAME        TEXT( 8 )          NOT NULL , 
           RT_OPERATIONNAME   TEXT( 32 )                  , 
           PAINTERDLL_NAME    TEXT( 8 )          NOT NULL , 
           PAINTERC_OPERATINN TEXT( 32 )                  , 
           PAINTERCNVRTOPRTNN TEXT( 32 )                  , 
           PAINTERBITMAP      TEXT( 6 )                   , 
           MAINTENANCEDIALOG  TEXT( 32 )                  , 
           MAINTENANCEWINDOW  TEXT( 32 )                  , 
           ACCEPTSALLPARENTS  TEXT( 1 )                   , 
           ACCEPTSALLCHILDREN TEXT( 1 )                   , 
           REQUIRESPARENT     TEXT( 1 )                   , 
           FORCEUPDATEONCREAT TEXT( 1 )                   , 
           ACTIVEX_SCRIPT     TEXT( 32 )                  , 
           ACTIVEX_SCRIPTDLL  TEXT( 32 )                  , 
           MAPTOOI            TEXT( 32 )                  , 
           MAPFROMOI          TEXT( 32 )                  , 
           FLAGS              INTEGER                     , 
           INVISIBLE          INTEGER                     , 
           z_GUID             TEXT( 64 )                  , 
           FK_ZKEY_PRESENVDEF INTEGER                     , 
           FK_ZKEY_CONTROLDEF INTEGER                      ) ;
 
CREATE UNIQUE INDEX CONTROLDEF_ZKEY 
       ON CONTROLDEF ( 
           ZKEY ) ;
 
CREATE INDEX CONTROLDEF_FK_ZKEY_PRESENVDE01 
       ON CONTROLDEF ( 
           FK_ZKEY_PRESENVDEF ) ;
 
CREATE INDEX CONTROLDEF_FK_ZKEY_CONTROLDE02 
       ON CONTROLDEF ( 
           FK_ZKEY_CONTROLDEF ) ;
 
-- Entity - CPL 
CREATE TABLE CPL ( 
           NAME               TEXT( 32 )         NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           z_DESC             MEMO                        , 
           FK_ZKEY_Z_USER     INTEGER                     , 
           FK_ZKEYINSTALLATIO INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX CPL_ID_CPL 
       ON CPL ( 
           ZKEY ) ;
 
CREATE INDEX CPL_FK_ZKEY_Z_USER01 
       ON CPL ( 
           FK_ZKEY_Z_USER ) ;
 
CREATE INDEX CPL_FK_ZKEYINSTALLATIO02 
       ON CPL ( 
           FK_ZKEYINSTALLATIO ) ;
 
-- Entity - CPL_ReuseableItem 
CREATE TABLE CPL_REUSEABLEITEM ( 
           ZKEY               INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX CPLREUSEABLEITEMIDCPLREUSEABLE 
       ON CPL_REUSEABLEITEM ( 
           ZKEY ) ;
 
-- Entity - CPLR 
CREATE TABLE CPLR ( 
           NAME               TEXT( 32 )         NOT NULL , 
           LASTCHECKINDATE    TEXT( 25 )                  , 
           ZKEY               INTEGER            NOT NULL , 
           z_DESC             MEMO                        , 
           METASRCDIR         TEXT( 127 )                 , 
           PGMSRCDIR          TEXT( 127 )                 , 
           EXECDIR            TEXT( 127 )                 , 
           DB_MODE            INTEGER                     , 
           FK_ZKEY_CPL        INTEGER                     , 
           FK_ZKEY_APPLICATIO INTEGER                      ) ;
 
CREATE UNIQUE INDEX CPLR_ID_CPLR 
       ON CPLR ( 
           ZKEY ) ;
 
CREATE INDEX CPLR_FK_ZKEY_CPL01 
       ON CPLR ( 
           FK_ZKEY_CPL ) ;
 
CREATE INDEX CPLR_FK_ZKEY_APPLICATIO02 
       ON CPLR ( 
           FK_ZKEY_APPLICATIO ) ;
 
-- Entity - CPLR_Enqueue 
CREATE TABLE CPLR_ENQUEUE ( 
           z_TIMESTAMP        TEXT( 25 )         NOT NULL , 
           ENQUEUETYPE        INTEGER                     , 
           USERNAME           TEXT( 32 )                  , 
           USERDESC           MEMO                        , 
           FK_ZKEY_CPLR       INTEGER            NOT NULL , 
           FKZKEYREPOSITORYCL INTEGER                      ) ;
 
CREATE UNIQUE INDEX CPLR_ENQUEUE_CPLR_MAYHAVEA 
       ON CPLR_ENQUEUE ( 
           FK_ZKEY_CPLR ) ;
 
CREATE INDEX CPLR_ENQUEUE_FK_ZKEY_CPLR01 
       ON CPLR_ENQUEUE ( 
           FK_ZKEY_CPLR ) ;
 
CREATE INDEX CPLRENQUEUEFKZKEYREPOSITORYC02 
       ON CPLR_ENQUEUE ( 
           FKZKEYREPOSITORYCL ) ;
 
-- Entity - DefinedItem 
CREATE TABLE DEFINEDITEM ( 
           EXTERNALVALUE      TEXT( 64 )                  , 
           ZKEY               INTEGER            NOT NULL , 
           INTERNALVALUE      TEXT( 254 )                 , 
           DATATYPE           TEXT( 1 )                   , 
           SEQNO              INTEGER                     , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_HEADERFILE INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX DEFINEDITEM_ID_DEFINEDITEM 
       ON DEFINEDITEM ( 
           ZKEY ) ;
 
CREATE INDEX DEFINEDITEM_FK_ZKEYHEADERFIL01 
       ON DEFINEDITEM ( 
           FK_ZKEY_HEADERFILE ) ;
 
-- Entity - DeliveryEnvPkg 
CREATE TABLE DELIVERYENVPKG ( 
           ZKEY               INTEGER            NOT NULL , 
           FK_ZKEY_APPLICATIO INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX DELIVERYENVPKGIDDELIVERYENVPAC 
       ON DELIVERYENVPKG ( 
           ZKEY ) ;
 
CREATE INDEX DELIVERYENVPKGFKZKEYAPPLICAT01 
       ON DELIVERYENVPKG ( 
           FK_ZKEY_APPLICATIO ) ;
 
-- Entity - Dialog 
CREATE TABLE DIALOG ( 
           TAG                TEXT( 8 )                   , 
           DLL_NAME           TEXT( 8 )                   , 
           ZKEY               INTEGER            NOT NULL , 
           z_DESC             MEMO                        , 
           FK_ZKEY_Z_METADEF  INTEGER                     , 
           FK_ZKEY_WINDOW     INTEGER                      ) ;
 
CREATE UNIQUE INDEX DIALOG_ID_DIALOG 
       ON DIALOG ( 
           ZKEY ) ;
 
CREATE INDEX DIALOG_FK_ZKEY_Z_METADEF01 
       ON DIALOG ( 
           FK_ZKEY_Z_METADEF ) ;
 
CREATE INDEX DIALOG_FK_ZKEY_WINDOW02 
       ON DIALOG ( 
           FK_ZKEY_WINDOW ) ;
 
-- Entity - Domain 
CREATE TABLE z_DOMAIN ( 
           ZKEY               INTEGER            NOT NULL , 
           NAME               TEXT( 32 )         NOT NULL , 
           z_DESC             MEMO                        , 
           DOMAINTYPE         TEXT( 1 )          NOT NULL , 
           DATATYPE           TEXT( 1 )          NOT NULL , 
           MAXSTRINGLTH       INTEGER                     , 
           CONTEXTRESTRICTION TEXT( 1 )                   , 
           DECIMALFORMAT      INTEGER                     , 
           FK_ZKEY_OPERATION  INTEGER                     , 
           FK_ZKEY_ADWINFOTYP INTEGER                     , 
           FK_ZKEY_Z_METADEF  INTEGER                     , 
           FK_ZKEY_SOURCEFILE INTEGER                      ) ;
 
CREATE UNIQUE INDEX z_DOMAIN_ID_DOMAIN 
       ON z_DOMAIN ( 
           ZKEY ) ;
 
CREATE INDEX z_DOMAIN_FK_ZKEY_OPERATION01 
       ON z_DOMAIN ( 
           FK_ZKEY_OPERATION ) ;
 
CREATE INDEX z_DOMAIN_FK_ZKEY_ADWINFOTYP02 
       ON z_DOMAIN ( 
           FK_ZKEY_ADWINFOTYP ) ;
 
CREATE INDEX z_DOMAIN_FK_ZKEY_Z_METADEF03 
       ON z_DOMAIN ( 
           FK_ZKEY_Z_METADEF ) ;
 
CREATE INDEX z_DOMAIN_FK_ZKEY_SOURCEFILE04 
       ON z_DOMAIN ( 
           FK_ZKEY_SOURCEFILE ) ;
 
-- Entity - EntpER_Model 
CREATE TABLE ENTPER_MODEL ( 
           NAME               TEXT( 32 )         NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           z_DESC             MEMO                        , 
           FK_ZKEY_Z_METADEF  INTEGER                      ) ;
 
CREATE UNIQUE INDEX ENTPER_MODEL_ID_ENTPER_MODEL 
       ON ENTPER_MODEL ( 
           ZKEY ) ;
 
CREATE INDEX ENTPER_MODEL_FK_ZKEY_ZMETADE01 
       ON ENTPER_MODEL ( 
           FK_ZKEY_Z_METADEF ) ;
 
-- Entity - ER_Attribute 
CREATE TABLE ER_ATTRIBUTE ( 
           NAME               TEXT( 32 )         NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           LTH                INTEGER                     , 
           z_KEY              TEXT( 1 )                   , 
           NOTNULL            TEXT( 1 )                   , 
           z_DESC             MEMO                        , 
           PROMPTPAINTLIT     TEXT( 60 )                  , 
           PROMPTPAINTLTH     INTEGER                     , 
           LISTPAINTLIT       TEXT( 60 )                  , 
           LISTPAINTLTH       INTEGER                     , 
           CASESENS           TEXT( 1 )                   , 
           ADW_POSITION       TEXT( 16 )                  , 
           TE_COLUMNNAME      TEXT( 32 )                  , 
           TE_FOREIGNKEYSUFFI TEXT( 20 )                  , 
           z_WORK             TEXT( 1 )                   , 
           DERIVEDEXPRESSION  TEXT( 254 )                 , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_ER_ENTITY  INTEGER                     , 
           FK_ZKEY_Z_DOMAIN   INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX ER_ATTRIBUTE_ID_ER_ATTRIBUTE 
       ON ER_ATTRIBUTE ( 
           ZKEY ) ;
 
CREATE INDEX ER_ATTRIBUTE_FK_ZKEY_ERENTIT01 
       ON ER_ATTRIBUTE ( 
           FK_ZKEY_ER_ENTITY ) ;
 
CREATE INDEX ER_ATTRIBUTE_FK_ZKEY_Z_DOMAI02 
       ON ER_ATTRIBUTE ( 
           FK_ZKEY_Z_DOMAIN ) ;
 
-- Entity - ER_EntIdentifier 
CREATE TABLE ER_ENTIDENTIFIER ( 
           NAME               TEXT( 32 )         NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           TYPE               TEXT( 1 )                   , 
           SYSTEMMAINTAINED   TEXT( 1 )                   , 
           z_DESC             MEMO                        , 
           TE_KEYNAME         TEXT( 32 )                  , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_ER_ENTITY  INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX ERENTIDENTIFIERIDERENTIDENTIFI 
       ON ER_ENTIDENTIFIER ( 
           ZKEY ) ;
 
CREATE INDEX ERENTIDENTIFIERFKZKEYERENTIT01 
       ON ER_ENTIDENTIFIER ( 
           FK_ZKEY_ER_ENTITY ) ;
 
-- Entity - ER_Entity 
CREATE TABLE ER_ENTITY ( 
           NAME               TEXT( 32 )         NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           PURPOSE            TEXT( 12 )                  , 
           z_DESC             MEMO                        , 
           OWNINGAREA         TEXT( 32 )                  , 
           ER_DIAGRAMPOSX     INTEGER                     , 
           ER_DIAGRAMPOSY     INTEGER                     , 
           ER_PORTFACTOR      INTEGER                     , 
           TE_TABLENAME       TEXT( 32 )                  , 
           TE_TABLEOWNER      TEXT( 32 )                  , 
           AUTOSEQ            INTEGER                     , 
           AUTOSEQ02          INTEGER                     , 
           FK_ZKEY_ENTPERMODE INTEGER                     , 
           FK_ZKEY_SUBJECTARE INTEGER                      ) ;
 
CREATE UNIQUE INDEX ER_ENTITY_ID_ER_ENTITY 
       ON ER_ENTITY ( 
           ZKEY ) ;
 
CREATE INDEX ER_ENTITY_FK_ZKEY_ENTPERMODE01 
       ON ER_ENTITY ( 
           FK_ZKEY_ENTPERMODE ) ;
 
CREATE INDEX ER_ENTITY_FK_ZKEY_SUBJECTARE02 
       ON ER_ENTITY ( 
           FK_ZKEY_SUBJECTARE ) ;
 
-- Entity - ER_FactType 
CREATE TABLE ER_FACTTYPE ( 
           ZKEY               INTEGER            NOT NULL , 
           AUTOSEQ            INTEGER                     , 
           AUTOSEQ02          INTEGER                     , 
           FKZKEYERENTIDENTIF INTEGER                     , 
           FK_ZKEY_ERATTRIBUT INTEGER                     , 
           FK_ZKEY_ER_RELLINK INTEGER                      ) ;
 
CREATE UNIQUE INDEX ER_FACTTYPE_ID_ER_FACTTYPE 
       ON ER_FACTTYPE ( 
           ZKEY ) ;
 
CREATE INDEX ER_FACTTYPEFKZKEYERENTIDENTI01 
       ON ER_FACTTYPE ( 
           FKZKEYERENTIDENTIF ) ;
 
CREATE INDEX ER_FACTTYPE_FK_ZKEYERATTRIBU02 
       ON ER_FACTTYPE ( 
           FK_ZKEY_ERATTRIBUT ) ;
 
CREATE INDEX ER_FACTTYPE_FK_ZKEY_ERRELLIN03 
       ON ER_FACTTYPE ( 
           FK_ZKEY_ER_RELLINK ) ;
 
-- Entity - ER_RelLink 
CREATE TABLE ER_RELLINK ( 
           NAME               TEXT( 32 )         NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           CARDMIN            TEXT( 8 )                   , 
           CARDMAX            TEXT( 8 )                   , 
           AUTOSEQ            TEXT( 1 )                   , 
           TE_FOREIGNKEYPREFI TEXT( 254 )                 , 
           TE_FOREIGNKEYSUFFI TEXT( 20 )                  , 
           HANGINGFORGNKYENTT TEXT( 1 )                   , 
           AUTOSEQ02          INTEGER                     , 
           AUTOSEQ03          INTEGER                     , 
           FK_ZKEY_ER_ENTITY  INTEGER            NOT NULL , 
           FK_ZKEY_ER_RELTYPE INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX ER_RELLINK_ID_ER_RELLINK 
       ON ER_RELLINK ( 
           ZKEY ) ;
 
CREATE INDEX ER_RELLINK_FK_ZKEY_ER_ENTITY01 
       ON ER_RELLINK ( 
           FK_ZKEY_ER_ENTITY ) ;
 
CREATE INDEX ER_RELLINK_FK_ZKEY_ER_RELTYP02 
       ON ER_RELLINK ( 
           FK_ZKEY_ER_RELTYPE ) ;
 
-- Entity - ER_RelType 
CREATE TABLE ER_RELTYPE ( 
           ZKEY               INTEGER            NOT NULL , 
           FACT               TEXT( 254 )                 , 
           ER_DIAGRAMBENDPOSX INTEGER                     , 
           ER_DIAGRAMBENDPOSY INTEGER                     , 
           ER_DIAGRAME1POSX   INTEGER                     , 
           ER_DIAGRAME1POSY   INTEGER                     , 
           ER_DIAGRAME2POSX   INTEGER                     , 
           ER_DIAGRAME2POSY   INTEGER                     , 
           FLAGS              INTEGER                     , 
           TE_TABLENAME       TEXT( 32 )                  , 
           AUTOSEQ            INTEGER                     , 
           AUTOSEQ02          INTEGER                     , 
           FK_ZKEY_SUBJECTARE INTEGER                     , 
           FK_ZKEY_ENTPERMODE INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX ER_RELTYPE_ID_ER_RELTYPE 
       ON ER_RELTYPE ( 
           ZKEY ) ;
 
CREATE INDEX ER_RELTYPE_FK_ZKEY_SUBJECTAR01 
       ON ER_RELTYPE ( 
           FK_ZKEY_SUBJECTARE ) ;
 
CREATE INDEX ER_RELTYPE_FK_ZKEY_ENTPERMOD02 
       ON ER_RELTYPE ( 
           FK_ZKEY_ENTPERMODE ) ;
 
-- Entity - Event 
CREATE TABLE EVENT ( 
           TYPE               INTEGER                     , 
           ZKEY               INTEGER            NOT NULL , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_CONTROL    INTEGER            NOT NULL , 
           FK_ZKEY_Z_ACTION   INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX EVENT_ID_EVENT 
       ON EVENT ( 
           ZKEY ) ;
 
CREATE INDEX EVENT_FK_ZKEY_CONTROL01 
       ON EVENT ( 
           FK_ZKEY_CONTROL ) ;
 
CREATE INDEX EVENT_FK_ZKEY_Z_ACTION02 
       ON EVENT ( 
           FK_ZKEY_Z_ACTION ) ;
 
-- Entity - EventDef 
CREATE TABLE EVENTDEF ( 
           ZKEY               INTEGER            NOT NULL , 
           TAG                TEXT( 32 )                  , 
           TYPE               INTEGER                     , 
           FK_ZKEY_WINDOWSTYL INTEGER                     , 
           FK_ZKEY_CONTROLDEF INTEGER                      ) ;
 
CREATE UNIQUE INDEX EVENTDEF_ZKEY 
       ON EVENTDEF ( 
           ZKEY ) ;
 
CREATE INDEX EVENTDEF_FK_ZKEY_WINDOWSTYL01 
       ON EVENTDEF ( 
           FK_ZKEY_WINDOWSTYL ) ;
 
CREATE INDEX EVENTDEF_FK_ZKEY_CONTROLDEF02 
       ON EVENTDEF ( 
           FK_ZKEY_CONTROLDEF ) ;
 
-- Entity - ExecComposite 
CREATE TABLE EXECCOMPOSITE ( 
           ZKEY               INTEGER            NOT NULL , 
           NAME               TEXT( 8 )                   , 
           FKZKEYDELIVERYENVP INTEGER                      ) ;
 
CREATE UNIQUE INDEX EXECCOMPOSITE_ID_Z_EXECMETACOM 
       ON EXECCOMPOSITE ( 
           ZKEY ) ;
 
CREATE INDEX EXECCOMPOSITEFKZKEYDELIVRYNV01 
       ON EXECCOMPOSITE ( 
           FKZKEYDELIVERYENVP ) ;
 
-- Entity - File 
CREATE TABLE z_FILE ( 
           ZKEY               INTEGER            NOT NULL , 
           NAME               TEXT( 8 )                   , 
           EXTENSION          TEXT( 3 )                   , 
           FK_ZKEY_CPLR       INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX z_FILE_ID_FILE 
       ON z_FILE ( 
           ZKEY ) ;
 
CREATE INDEX z_FILE_FK_ZKEY_CPLR01 
       ON z_FILE ( 
           FK_ZKEY_CPLR ) ;
 
-- Entity - Font 
CREATE TABLE FONT ( 
           ZKEY               INTEGER            NOT NULL , 
           TAG                TEXT( 32 )                  , 
           ID                 INTEGER                     , 
           WINDOWSSTRUCTURE   LONGBINARY                  , 
           RGB_COLOR          INTEGER                     , 
           POINTSIZE          INTEGER                     , 
           INVISIBLE          INTEGER                     , 
           FK_ZKEY_PRESENVDEF INTEGER                      ) ;
 
CREATE UNIQUE INDEX FONT_ZKEY 
       ON FONT ( 
           ZKEY ) ;
 
CREATE INDEX FONT_FK_ZKEY_PRESENVDEF01 
       ON FONT ( 
           FK_ZKEY_PRESENVDEF ) ;
 
-- Entity - FontDef 
CREATE TABLE FONTDEF ( 
           ZKEY               INTEGER            NOT NULL , 
           TAG                TEXT( 32 )                  , 
           SEQNO              INTEGER                     , 
           FK_ZKEY_CONTROLDEF INTEGER                     , 
           FK_ZKEY_FONT       INTEGER            NOT NULL , 
           FK_ZKEY_WINDOWSTYL INTEGER                      ) ;
 
CREATE UNIQUE INDEX FONTDEF_ZKEY 
       ON FONTDEF ( 
           ZKEY ) ;
 
CREATE INDEX FONTDEF_FK_ZKEY_CONTROLDEF01 
       ON FONTDEF ( 
           FK_ZKEY_CONTROLDEF ) ;
 
CREATE INDEX FONTDEF_FK_ZKEY_FONT02 
       ON FONTDEF ( 
           FK_ZKEY_FONT ) ;
 
CREATE INDEX FONTDEF_FK_ZKEY_WINDOWSTYL03 
       ON FONTDEF ( 
           FK_ZKEY_WINDOWSTYL ) ;
 
-- Entity - FontOverride 
CREATE TABLE FONTOVERRIDE ( 
           ZKEY               INTEGER            NOT NULL , 
           SEQNO_DLGCTRL      INTEGER                     , 
           SEQNO_DLGWND       INTEGER                     , 
           FK_ZKEY_CONTROL    INTEGER                     , 
           FK_ZKEY_FONTDEF    INTEGER                     , 
           FK_ZKEY_FONT       INTEGER            NOT NULL , 
           FK_ZKEY_WINDOW     INTEGER                      ) ;
 
CREATE UNIQUE INDEX FONTOVERRIDE_ZKEY 
       ON FONTOVERRIDE ( 
           ZKEY ) ;
 
CREATE INDEX FONTOVERRIDE_FK_ZKEY_CONTROL01 
       ON FONTOVERRIDE ( 
           FK_ZKEY_CONTROL ) ;
 
CREATE INDEX FONTOVERRIDE_FK_ZKEY_FONTDEF02 
       ON FONTOVERRIDE ( 
           FK_ZKEY_FONTDEF ) ;
 
CREATE INDEX FONTOVERRIDE_FK_ZKEY_FONT03 
       ON FONTOVERRIDE ( 
           FK_ZKEY_FONT ) ;
 
CREATE INDEX FONTOVERRIDE_FK_ZKEY_WINDOW04 
       ON FONTOVERRIDE ( 
           FK_ZKEY_WINDOW ) ;
 
-- Entity - Group 
CREATE TABLE z_GROUP ( 
           ZKEY               INTEGER            NOT NULL , 
           ALLOWPAGEBREAK     TEXT( 1 )                   , 
           TAG                TEXT( 32 )                  , 
           z_TEXT             TEXT( 254 )                 , 
           TYPE               TEXT( 2 )                   , 
           SUBTYPE            TEXT( 1 )                   , 
           PSDLG_X            INTEGER                     , 
           PSDLG_Y            INTEGER                     , 
           SZDLG_X            INTEGER                     , 
           SZDLG_Y            INTEGER                     , 
           SYNCKEY            INTEGER                     , 
           PPE_TYPE           INTEGER                     , 
           FORCEHEADERPERENTT TEXT( 1 )                   , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_GROUPSET   INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX z_GROUP_ID_GROUP 
       ON z_GROUP ( 
           ZKEY ) ;
 
CREATE INDEX z_GROUP_FK_ZKEY_GROUPSET01 
       ON z_GROUP ( 
           FK_ZKEY_GROUPSET ) ;
 
-- Entity - GroupSet 
CREATE TABLE GROUPSET ( 
           ZKEY               INTEGER            NOT NULL , 
           TAG                TEXT( 32 )                  , 
           z_TEXT             TEXT( 254 )                 , 
           TYPE               TEXT( 2 )                   , 
           SUBTYPE            INTEGER                     , 
           PSDLG_X            INTEGER                     , 
           PSDLG_Y            INTEGER                     , 
           SZDLG_X            INTEGER                     , 
           SZDLG_Y            INTEGER                     , 
           SYNCKEY            INTEGER                     , 
           PPE_TYPE           INTEGER                     , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_PAGE       INTEGER            NOT NULL , 
           FK_ZKEY_LOD_ENTITY INTEGER                      ) ;
 
CREATE UNIQUE INDEX GROUPSET_ID_GROUPSET 
       ON GROUPSET ( 
           ZKEY ) ;
 
CREATE INDEX GROUPSET_FK_ZKEY_PAGE01 
       ON GROUPSET ( 
           FK_ZKEY_PAGE ) ;
 
CREATE INDEX GROUPSET_FK_ZKEY_LOD_ENTITY02 
       ON GROUPSET ( 
           FK_ZKEY_LOD_ENTITY ) ;
 
-- Entity - HeaderFile 
CREATE TABLE HEADERFILE ( 
           NAME               TEXT( 8 )          NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           z_DESC             MEMO                        , 
           EXTENSION          TEXT( 3 )                   , 
           FK_ZKEY_Z_METADEF  INTEGER                      ) ;
 
CREATE UNIQUE INDEX HEADERFILE_ID_HEADERFILE 
       ON HEADERFILE ( 
           ZKEY ) ;
 
CREATE INDEX HEADERFILE_FK_ZKEY_Z_METADEF01 
       ON HEADERFILE ( 
           FK_ZKEY_Z_METADEF ) ;
 
-- Entity - Hotkey 
CREATE TABLE HOTKEY ( 
           ZKEY               INTEGER            NOT NULL , 
           TAG                TEXT( 32 )                  , 
           KEYCOMBO           LONGBINARY                  , 
           TITLE              TEXT( 32 )                  , 
           MODE               INTEGER                     , 
           VKEY               INTEGER                     , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_WINDOW     INTEGER                     , 
           FK_ZKEY_Z_ACTION   INTEGER                      ) ;
 
CREATE UNIQUE INDEX HOTKEY_HOTKEYKEY 
       ON HOTKEY ( 
           ZKEY ) ;
 
CREATE INDEX HOTKEY_FK_ZKEY_WINDOW01 
       ON HOTKEY ( 
           FK_ZKEY_WINDOW ) ;
 
CREATE INDEX HOTKEY_FK_ZKEY_Z_ACTION02 
       ON HOTKEY ( 
           FK_ZKEY_Z_ACTION ) ;
 
-- Entity - Installation 
CREATE TABLE INSTALLATION ( 
           NAME               TEXT( 32 )         NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           SYSADM             TEXT( 32 )         NOT NULL , 
           z_PASSWORD         TEXT( 8 )                   , 
           NEXTWKS_ID         INTEGER                     , 
           NEXTINSTALLZKEY    INTEGER                     , 
           z_DESC             MEMO                         ) ;
 
CREATE UNIQUE INDEX INSTALLATION_ID_INSTALLATION 
       ON INSTALLATION ( 
           ZKEY ) ;
 
-- Entity - LOD 
CREATE TABLE LOD ( 
           ZKEY               INTEGER            NOT NULL , 
           DLL_NAME           TEXT( 8 )                   , 
           NAME               TEXT( 8 )          NOT NULL , 
           z_DESC             MEMO                        , 
           ACTIVATECONSTRAINT TEXT( 1 )                   , 
           ACTIVATESRVRCNSTRN TEXT( 1 )                   , 
           ACTIVATEMPTYCNSTRN TEXT( 1 )                   , 
           COMMITCONSTRAINT   TEXT( 1 )                   , 
           COMMITSERVERCNSTRN TEXT( 1 )                   , 
           DROPOICONSTRAINT   TEXT( 1 )                   , 
           CACHENUMBERPERENTT INTEGER                     , 
           DATALOCKING        INTEGER                     , 
           FK_ZKEY_OPERATION  INTEGER                     , 
           FK_ZKEY_LOD_ENTITY INTEGER            NOT NULL , 
           FK_ZKEY_Z_METADEF  INTEGER                      ) ;
 
CREATE UNIQUE INDEX LOD_ID_LOD 
       ON LOD ( 
           ZKEY ) ;
 
CREATE INDEX LOD_FK_ZKEY_OPERATION01 
       ON LOD ( 
           FK_ZKEY_OPERATION ) ;
 
CREATE INDEX LOD_FK_ZKEY_LOD_ENTITY02 
       ON LOD ( 
           FK_ZKEY_LOD_ENTITY ) ;
 
CREATE INDEX LOD_FK_ZKEY_Z_METADEF03 
       ON LOD ( 
           FK_ZKEY_Z_METADEF ) ;
 
-- Entity - LOD_Attribute 
CREATE TABLE LOD_ATTRIBUTE ( 
           ZKEY               INTEGER            NOT NULL , 
           z_WORK             TEXT( 1 )                   , 
           z_UPDATE           TEXT( 1 )                   , 
           INIT               TEXT( 254 )                 , 
           HIDDEN             TEXT( 1 )                   , 
           SEQPRIORITY        INTEGER                     , 
           SEQORDER           TEXT( 1 )                   , 
           DIL_TEXT           TEXT( 254 )                 , 
           SEQNO_LOD_ENTITY   INTEGER                     , 
           SEQNO_UIS_ENTITY_M INTEGER                     , 
           SEQNO_UIS_ENTITY_L INTEGER                     , 
           DB_DERIVEDVALUE    TEXT( 1 )                   , 
           AUTOSEQ            INTEGER                     , 
           AUTOSEQ02          INTEGER                     , 
           FK_ZKEY_ERATTRIBUT INTEGER                     , 
           FK_ZKEY_UIS_ENTITY INTEGER                     , 
           FK_ZKEY_OPERATION  INTEGER                     , 
           FK_ZKEY_ERATTRIB02 INTEGER                     , 
           FK_ZKEY_LOD_ENTITY INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX LOD_ATTRIBUTE_ID_LOD_ATTRIBUTE 
       ON LOD_ATTRIBUTE ( 
           ZKEY ) ;
 
CREATE INDEX LOD_ATTRIBUTEFKZKEYERATTRIBU01 
       ON LOD_ATTRIBUTE ( 
           FK_ZKEY_ERATTRIBUT ) ;
 
CREATE INDEX LOD_ATTRIBUTE_FKZKEYUISENTIT02 
       ON LOD_ATTRIBUTE ( 
           FK_ZKEY_UIS_ENTITY ) ;
 
CREATE INDEX LOD_ATTRIBUTE_FKZKEYOPERATIO03 
       ON LOD_ATTRIBUTE ( 
           FK_ZKEY_OPERATION ) ;
 
CREATE INDEX LOD_ATTRIBUTEFKZKEYERATTRIB004 
       ON LOD_ATTRIBUTE ( 
           FK_ZKEY_ERATTRIB02 ) ;
 
CREATE INDEX LOD_ATTRIBUTE_FKZKEYLODENTIT05 
       ON LOD_ATTRIBUTE ( 
           FK_ZKEY_LOD_ENTITY ) ;
 
-- Entity - LOD_Entity 
CREATE TABLE LOD_ENTITY ( 
           NAME               TEXT( 32 )         NOT NULL , 
           INDENTNAME         TEXT( 100 )                 , 
           INDENTLVL          INTEGER                     , 
           ZKEY               INTEGER            NOT NULL , 
           z_CREATE           TEXT( 1 )                   , 
           z_DELETE           TEXT( 1 )                   , 
           INCLUDE            TEXT( 1 )                   , 
           INCLSRC            TEXT( 1 )                   , 
           EXCLUDE            TEXT( 1 )                   , 
           HIDDEN             TEXT( 1 )                   , 
           RECURSIVE          TEXT( 1 )                   , 
           AUTOCREATE         TEXT( 1 )                   , 
           DERIVED            TEXT( 1 )                   , 
           z_UPDATE           TEXT( 1 )                   , 
           SEQTYPE            TEXT( 1 )                   , 
           z_WORK             TEXT( 1 )                   , 
           PARENTDELETEBEHAVE TEXT( 1 )                   , 
           DUPENTITYINSTANCE  TEXT( 1 )                   , 
           DUPRELATINSHPINSTN TEXT( 1 )                   , 
           RELLINKINDICATOR   TEXT( 1 )                   , 
           z_DESC             MEMO                        , 
           CREATECONSTRAINT   TEXT( 1 )                   , 
           DELETECONSTRAINT   TEXT( 1 )                   , 
           INCLUDECONSTRAINT  TEXT( 1 )                   , 
           EXCLUDECONSTRAINT  TEXT( 1 )                   , 
           ACCEPTCONSTRAINT   TEXT( 1 )                   , 
           CANCELCONSTRAINT   TEXT( 1 )                   , 
           SEQNO              INTEGER                     , 
           DATALOCKING        INTEGER                     , 
           MULTIPLECHILDLIMIT INTEGER                     , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_OPERATION  INTEGER                     , 
           FK_ZKEY_ER_ENTITY  INTEGER                     , 
           FK_ZKEY_ER_RELLINK INTEGER                     , 
           FK_ZKEY_LOD_ENTITY INTEGER                      ) ;
 
CREATE UNIQUE INDEX LOD_ENTITY_ID_LOD_ENTITY 
       ON LOD_ENTITY ( 
           ZKEY ) ;
 
CREATE INDEX LOD_ENTITY_FK_ZKEY_OPERATION01 
       ON LOD_ENTITY ( 
           FK_ZKEY_OPERATION ) ;
 
CREATE INDEX LOD_ENTITY_FK_ZKEY_ER_ENTITY02 
       ON LOD_ENTITY ( 
           FK_ZKEY_ER_ENTITY ) ;
 
CREATE INDEX LOD_ENTITY_FK_ZKEY_ER_RELLIN03 
       ON LOD_ENTITY ( 
           FK_ZKEY_ER_RELLINK ) ;
 
CREATE INDEX LOD_ENTITY_FK_ZKEY_LOD_ENTIT04 
       ON LOD_ENTITY ( 
           FK_ZKEY_LOD_ENTITY ) ;
 
-- Entity - LPLR 
CREATE TABLE LPLR ( 
           NAME               TEXT( 8 )          NOT NULL , 
           z_DESC             MEMO                        , 
           ZKEY               INTEGER            NOT NULL , 
           PGMSRCDIR          TEXT( 127 )                 , 
           EXECDIR            TEXT( 127 )                 , 
           METASRCDIR         TEXT( 127 )                 , 
           TASKUSECOUNT       INTEGER                     , 
           LASTREFRESHDATE    TEXT( 25 )                  , 
           FK_ZKEY_CPLR       INTEGER                     , 
           FKZKEYREPOSITORYCL INTEGER                      ) ;
 
CREATE UNIQUE INDEX LPLR_ID_LPLR 
       ON LPLR ( 
           ZKEY ) ;
 
CREATE INDEX LPLR_FK_ZKEY_CPLR01 
       ON LPLR ( 
           FK_ZKEY_CPLR ) ;
 
CREATE INDEX LPLR_FKZKEYREPOSITORYCL02 
       ON LPLR ( 
           FKZKEYREPOSITORYCL ) ;
 
-- Entity - MapDef 
CREATE TABLE MAPDEF ( 
           ZKEY               INTEGER            NOT NULL , 
           z_DESC             MEMO                        , 
           TAG                TEXT( 32 )                  , 
           TYPE               TEXT( 1 )          NOT NULL , 
           ITERATOR           TEXT( 1 )                   , 
           FK_ZKEY_CONTROLDEF INTEGER                      ) ;
 
CREATE UNIQUE INDEX MAPDEF_ZKEY 
       ON MAPDEF ( 
           ZKEY ) ;
 
CREATE INDEX MAPDEF_FK_ZKEY_CONTROLDEF01 
       ON MAPDEF ( 
           FK_ZKEY_CONTROLDEF ) ;
 
-- Entity - MapRef 
CREATE TABLE MAPREF ( 
           TAG                TEXT( 32 )                  , 
           ZKEY               INTEGER            NOT NULL , 
           TYPE               TEXT( 1 )                   , 
           SEQNO_DLGCTRL      INTEGER                     , 
           SEQNO_DLGACT       INTEGER                     , 
           AUTOSEQ            INTEGER                     , 
           AUTOSEQ02          INTEGER                     , 
           AUTOSEQ03          INTEGER                     , 
           AUTOSEQ04          INTEGER                     , 
           AUTOSEQ05          INTEGER                     , 
           FK_ZKEY_WINDOW     INTEGER                     , 
           FK_ZKEYLODATTRIBUT INTEGER                     , 
           FK_ZKEY_LOD_ENTITY INTEGER                     , 
           FK_ZKEY_CONTEXT    INTEGER                     , 
           FK_ZKEY_Z_ACTION   INTEGER                     , 
           FK_ZKEY_CONTROL    INTEGER                     , 
           FK_ZKEY_VIEWOBJREF INTEGER                      ) ;
 
CREATE UNIQUE INDEX MAPREF_ID_MAPREF 
       ON MAPREF ( 
           ZKEY ) ;
 
CREATE INDEX MAPREF_FK_ZKEY_WINDOW01 
       ON MAPREF ( 
           FK_ZKEY_WINDOW ) ;
 
CREATE INDEX MAPREF_FK_ZKEYLODATTRIBUT02 
       ON MAPREF ( 
           FK_ZKEYLODATTRIBUT ) ;
 
CREATE INDEX MAPREF_FK_ZKEY_LOD_ENTITY03 
       ON MAPREF ( 
           FK_ZKEY_LOD_ENTITY ) ;
 
CREATE INDEX MAPREF_FK_ZKEY_CONTEXT04 
       ON MAPREF ( 
           FK_ZKEY_CONTEXT ) ;
 
CREATE INDEX MAPREF_FK_ZKEY_Z_ACTION05 
       ON MAPREF ( 
           FK_ZKEY_Z_ACTION ) ;
 
CREATE INDEX MAPREF_FK_ZKEY_CONTROL06 
       ON MAPREF ( 
           FK_ZKEY_CONTROL ) ;
 
CREATE INDEX MAPREF_FK_ZKEY_VIEWOBJREF07 
       ON MAPREF ( 
           FK_ZKEY_VIEWOBJREF ) ;
 
-- Entity - Menu 
CREATE TABLE MENU ( 
           TAG                TEXT( 32 )                  , 
           ZKEY               INTEGER            NOT NULL , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_WINDOW     INTEGER                     , 
           FK_ZKEY_WINDOW02   INTEGER                      ) ;
 
CREATE UNIQUE INDEX MENU_ID_MENU 
       ON MENU ( 
           ZKEY ) ;
 
CREATE INDEX MENU_FK_ZKEY_WINDOW01 
       ON MENU ( 
           FK_ZKEY_WINDOW ) ;
 
CREATE INDEX MENU_FK_ZKEY_WINDOW0202 
       ON MENU ( 
           FK_ZKEY_WINDOW02 ) ;
 
-- Entity - NLS_Text 
CREATE TABLE NLS_TEXT ( 
           z_TEXT             TEXT( 254 )                 , 
           LANGUAGEINDEX      INTEGER            NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           AUTOSEQ            INTEGER                     , 
           AUTOSEQ02          INTEGER                     , 
           AUTOSEQ03          INTEGER                     , 
           AUTOSEQ04          INTEGER                     , 
           AUTOSEQ05          INTEGER                     , 
           AUTOSEQ06          INTEGER                     , 
           AUTOSEQ07          INTEGER                     , 
           FK_ZKEY_Z_OPTION   INTEGER                     , 
           FK_ZKEY_CONTROL    INTEGER                     , 
           FK_ZKEY_CONTEXT    INTEGER                     , 
           FK_ZKEY_CONTROL02  INTEGER                     , 
           FK_ZKEYLODATTRIBUT INTEGER                     , 
           FK_ZKEY_Z_OPTION02 INTEGER                     , 
           FK_ZKEY_TABLEENTRY INTEGER                     , 
           FK_ZKEY_WINDOW     INTEGER                      ) ;
 
CREATE UNIQUE INDEX NLS_TEXT_ID_NLS_TEXT 
       ON NLS_TEXT ( 
           ZKEY ) ;
 
CREATE INDEX NLS_TEXT_FK_ZKEY_Z_OPTION01 
       ON NLS_TEXT ( 
           FK_ZKEY_Z_OPTION ) ;
 
CREATE INDEX NLS_TEXT_FK_ZKEY_CONTROL02 
       ON NLS_TEXT ( 
           FK_ZKEY_CONTROL ) ;
 
CREATE INDEX NLS_TEXT_FK_ZKEY_CONTEXT03 
       ON NLS_TEXT ( 
           FK_ZKEY_CONTEXT ) ;
 
CREATE INDEX NLS_TEXT_FK_ZKEY_CONTROL0204 
       ON NLS_TEXT ( 
           FK_ZKEY_CONTROL02 ) ;
 
CREATE INDEX NLS_TEXT_FK_ZKEYLODATTRIBUT05 
       ON NLS_TEXT ( 
           FK_ZKEYLODATTRIBUT ) ;
 
CREATE INDEX NLS_TEXT_FK_ZKEY_Z_OPTION0206 
       ON NLS_TEXT ( 
           FK_ZKEY_Z_OPTION02 ) ;
 
CREATE INDEX NLS_TEXT_FK_ZKEY_TABLEENTRY07 
       ON NLS_TEXT ( 
           FK_ZKEY_TABLEENTRY ) ;
 
CREATE INDEX NLS_TEXT_FK_ZKEY_WINDOW08 
       ON NLS_TEXT ( 
           FK_ZKEY_WINDOW ) ;
 
-- Entity - Operation 
CREATE TABLE OPERATION ( 
           NAME               TEXT( 32 )         NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           z_DESC             MEMO                        , 
           TYPE               TEXT( 1 )          NOT NULL , 
           RETURNDESC         TEXT( 64 )                  , 
           RETURNDATATYPE     TEXT( 1 )                   , 
           ORDINALVALUE       INTEGER                     , 
           CLASS              INTEGER                     , 
           FK_ZKEY_SOURCEFILE INTEGER                     , 
           FK_ZKEY_Z_METADEF  INTEGER                     , 
           FK_ZKEY_HEADERFILE INTEGER                     , 
           FK_ZKEY_SOURCEFI02 INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX OPERATION_ID_OPERATION 
       ON OPERATION ( 
           ZKEY ) ;
 
CREATE INDEX OPERATION_FK_ZKEY_SOURCEFILE01 
       ON OPERATION ( 
           FK_ZKEY_SOURCEFILE ) ;
 
CREATE INDEX OPERATION_FK_ZKEY_Z_METADEF02 
       ON OPERATION ( 
           FK_ZKEY_Z_METADEF ) ;
 
CREATE INDEX OPERATION_FK_ZKEY_HEADERFILE03 
       ON OPERATION ( 
           FK_ZKEY_HEADERFILE ) ;
 
CREATE INDEX OPERATION_FK_ZKEY_SOURCEFI0204 
       ON OPERATION ( 
           FK_ZKEY_SOURCEFI02 ) ;
 
-- Entity - Option 
CREATE TABLE z_OPTION ( 
           TAG                TEXT( 32 )                  , 
           z_TEXT             TEXT( 32 )                  , 
           ACCELTITLE         TEXT( 32 )                  , 
           CHECKMARKVALUEON   TEXT( 64 )                  , 
           CHECKMARKVALUEOFF  TEXT( 64 )                  , 
           SEPARATOR          TEXT( 1 )                   , 
           ZKEY               INTEGER            NOT NULL , 
           UNDERLINE          INTEGER                     , 
           DIL_TEXT           TEXT( 254 )                 , 
           SEQNO_MENU         INTEGER                     , 
           SEQNO_OPTION       INTEGER                     , 
           AUTOSEQ            INTEGER                     , 
           AUTOSEQ02          INTEGER                     , 
           FK_ZKEY_MENU       INTEGER                     , 
           FK_ZKEY_Z_OPTION   INTEGER                     , 
           FK_ZKEY_MAPREF     INTEGER                     , 
           FK_ZKEY_Z_ACTION   INTEGER                      ) ;
 
CREATE UNIQUE INDEX z_OPTION_ID_OPTION 
       ON z_OPTION ( 
           ZKEY ) ;
 
CREATE INDEX z_OPTION_FK_ZKEY_MENU01 
       ON z_OPTION ( 
           FK_ZKEY_MENU ) ;
 
CREATE INDEX z_OPTION_FK_ZKEY_Z_OPTION02 
       ON z_OPTION ( 
           FK_ZKEY_Z_OPTION ) ;
 
CREATE INDEX z_OPTION_FK_ZKEY_MAPREF03 
       ON z_OPTION ( 
           FK_ZKEY_MAPREF ) ;
 
CREATE INDEX z_OPTION_FK_ZKEY_Z_ACTION04 
       ON z_OPTION ( 
           FK_ZKEY_Z_ACTION ) ;
 
-- Entity - OrigSironField 
CREATE TABLE ORIGSIRONFIELD ( 
           ZKEY               INTEGER            NOT NULL , 
           KATALOGFLAG        TEXT( 1 )                   , 
           ATTRIBUT           TEXT( 2 )                   , 
           FIELDNR            INTEGER                     , 
           z_LEVEL            INTEGER                     , 
           STHK               INTEGER                     , 
           OCCURSNR           INTEGER                     , 
           KEYCODE            TEXT( 2 )                   , 
           DIMENSION          INTEGER                     , 
           LENGTH             INTEGER                     , 
           RELADR             INTEGER                     , 
           ADDITOR            INTEGER                     , 
           FIELDNAME          TEXT( 33 )                  , 
           AUTOSEQ            INTEGER                     , 
           AUTOSEQ02          INTEGER                     , 
           FKZKEYORIGSIRONFIE INTEGER                     , 
           FK_ZKEYSIRONKATALO INTEGER                      ) ;
 
CREATE UNIQUE INDEX ORIGSIRONFIELD_ZKEY 
       ON ORIGSIRONFIELD ( 
           ZKEY ) ;
 
CREATE INDEX ORIGSIRONFIELDFKZKEYORIGSIRN01 
       ON ORIGSIRONFIELD ( 
           FKZKEYORIGSIRONFIE ) ;
 
CREATE INDEX ORIGSIRONFIELDFKZKEYSIRONKAT02 
       ON ORIGSIRONFIELD ( 
           FK_ZKEYSIRONKATALO ) ;
 
-- Entity - Page 
CREATE TABLE PAGE ( 
           ZKEY               INTEGER            NOT NULL , 
           TAG                TEXT( 32 )                  , 
           TYPE               TEXT( 1 )                   , 
           SIZEX              INTEGER                     , 
           SIZEY              INTEGER                     , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_REPORT     INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX PAGE_ID_PAGE 
       ON PAGE ( 
           ZKEY ) ;
 
CREATE INDEX PAGE_FK_ZKEY_REPORT01 
       ON PAGE ( 
           FK_ZKEY_REPORT ) ;
 
-- Entity - Parameter 
CREATE TABLE PARAMETER ( 
           SHORTDESC          TEXT( 64 )         NOT NULL , 
           DATATYPE           TEXT( 1 )          NOT NULL , 
           PFLAG              TEXT( 1 )                   , 
           UFLAG              TEXT( 1 )                   , 
           ZKEY               INTEGER            NOT NULL , 
           SEQNO              INTEGER                     , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_OPERATION  INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX PARAMETER_ID_PARAMETER 
       ON PARAMETER ( 
           ZKEY ) ;
 
CREATE INDEX PARAMETER_FK_ZKEY_OPERATION01 
       ON PARAMETER ( 
           FK_ZKEY_OPERATION ) ;
 
-- Entity - PhysOverride 
CREATE TABLE PHYSOVERRIDE ( 
           ZKEY               INTEGER            NOT NULL , 
           FK_ZKEY_FONT       INTEGER                      ) ;
 
CREATE UNIQUE INDEX PHYSOVERRIDE_ZKEY 
       ON PHYSOVERRIDE ( 
           ZKEY ) ;
 
CREATE INDEX PHYSOVERRIDE_FK_ZKEY_FONT01 
       ON PHYSOVERRIDE ( 
           FK_ZKEY_FONT ) ;
 
-- Entity - POD 
CREATE TABLE POD ( 
           NAME               TEXT( 32 )         NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           z_DESC             MEMO                        , 
           DFT_DBNAME         TEXT( 32 )                  , 
           DFT_SERVER         TEXT( 32 )                  , 
           OPER_LIBNM         TEXT( 8 )                   , 
           CR_DATE            TEXT( 18 )                  , 
           UP_DATE            TEXT( 18 )                  , 
           USERID             TEXT( 32 )                  , 
           MULTIPLE_ROOT_LIMI INTEGER                     , 
           TE_SOURCEZKEY      INTEGER                     , 
           FK_ZKEY_TEDBENVIRO INTEGER                     , 
           FK_ZKEY_LOD        INTEGER            NOT NULL , 
           FK_ZKEY_POD_ENTITY INTEGER                     , 
           FK_ZKEY_Z_METADEF  INTEGER                      ) ;
 
CREATE UNIQUE INDEX POD_ID_POD 
       ON POD ( 
           ZKEY ) ;
 
CREATE INDEX POD_FK_ZKEY_TEDBENVIRO01 
       ON POD ( 
           FK_ZKEY_TEDBENVIRO ) ;
 
CREATE INDEX POD_FK_ZKEY_LOD02 
       ON POD ( 
           FK_ZKEY_LOD ) ;
 
CREATE INDEX POD_FK_ZKEY_POD_ENTITY03 
       ON POD ( 
           FK_ZKEY_POD_ENTITY ) ;
 
CREATE INDEX POD_FK_ZKEY_Z_METADEF04 
       ON POD ( 
           FK_ZKEY_Z_METADEF ) ;
 
-- Entity - POD_Attribute 
CREATE TABLE POD_ATTRIBUTE ( 
           NAME               TEXT( 32 )         NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           SEQNR              INTEGER            NOT NULL , 
           ERATT              INTEGER                     , 
           TYPE               TEXT( 1 )                   , 
           LTH                INTEGER                     , 
           z_DECIMAL          INTEGER                     , 
           INIT               TEXT( 254 )                 , 
           PERSIST            TEXT( 1 )                   , 
           z_KEY              TEXT( 1 )                   , 
           GENKEY             TEXT( 1 )                   , 
           REQUIRED           TEXT( 1 )                   , 
           CASESENS           TEXT( 1 )                   , 
           SEQUENCING         INTEGER                     , 
           SEQ_AD             TEXT( 1 )                   , 
           AUTO_SEQ           TEXT( 1 )                   , 
           HIDDEN             TEXT( 1 )                   , 
           CR_DATE            TEXT( 1 )                   , 
           UP_DATE            TEXT( 1 )                   , 
           USERID             TEXT( 1 )                   , 
           FK_ZKEYLODATTRIBUT INTEGER                     , 
           FK_ZKEY_POD_ENTITY INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX POD_ATTRIBUTE_ID_POD_ATTRIBUTE 
       ON POD_ATTRIBUTE ( 
           ZKEY ) ;
 
CREATE INDEX PODATTRIBUTEFKZKEYLODATTRIBU01 
       ON POD_ATTRIBUTE ( 
           FK_ZKEYLODATTRIBUT ) ;
 
CREATE INDEX POD_ATTRIBUTE_FKZKEYPODENTIT02 
       ON POD_ATTRIBUTE ( 
           FK_ZKEY_POD_ENTITY ) ;
 
-- Entity - POD_Entity 
CREATE TABLE POD_ENTITY ( 
           NAME               TEXT( 32 )         NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           SEQNR              INTEGER            NOT NULL , 
           SERVER             TEXT( 32 )                  , 
           DBNAME             TEXT( 32 )                  , 
           FULLPERSIST        TEXT( 1 )                   , 
           ERENT_TOK          INTEGER            NOT NULL , 
           ERREL_TOK          INTEGER            NOT NULL , 
           z_LEVEL            INTEGER            NOT NULL , 
           CARDMIN            INTEGER            NOT NULL , 
           CARDMAX            INTEGER            NOT NULL , 
           z_CREATE           TEXT( 1 )                   , 
           z_DELETE           TEXT( 1 )                   , 
           INCLUDE            TEXT( 1 )                   , 
           EXCLUDE            TEXT( 1 )                   , 
           HIDDEN             TEXT( 1 )                   , 
           RECURSIVE          TEXT( 1 )                   , 
           AUTOCREATE         TEXT( 1 )                   , 
           FK_ZKEY_LOD_ENTITY INTEGER                     , 
           FK_ZKEY_POD_ENTITY INTEGER                      ) ;
 
CREATE UNIQUE INDEX POD_ENTITY_ID_POD_ENTITY 
       ON POD_ENTITY ( 
           ZKEY ) ;
 
CREATE INDEX POD_ENTITY_FK_ZKEY_LOD_ENTIT01 
       ON POD_ENTITY ( 
           FK_ZKEY_LOD_ENTITY ) ;
 
CREATE INDEX POD_ENTITY_FK_ZKEY_POD_ENTIT02 
       ON POD_ENTITY ( 
           FK_ZKEY_POD_ENTITY ) ;
 
-- Entity - POD_EntityMapFld 
CREATE TABLE POD_ENTITYMAPFLD ( 
           ZKEY               INTEGER            NOT NULL , 
           SEQNR              INTEGER            NOT NULL , 
           FLDNAME            TEXT( 32 )                  , 
           FLDID              INTEGER                     , 
           FLDTYPE            TEXT( 1 )                   , 
           FLDLTH             INTEGER                     , 
           FLDOFFSET          INTEGER                     , 
           FK_ZKEYPODATTRIBUT INTEGER                     , 
           FKZKEYPODENTITYMAP INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX PODENTITYMAPFLDIDPODENTITYMAPF 
       ON POD_ENTITYMAPFLD ( 
           ZKEY ) ;
 
CREATE INDEX PODENTITYMAPFLDFKZKEYPODTTRB01 
       ON POD_ENTITYMAPFLD ( 
           FK_ZKEYPODATTRIBUT ) ;
 
CREATE INDEX PODENTITYMAPFLDFKZKEYPDNTTYM02 
       ON POD_ENTITYMAPFLD ( 
           FKZKEYPODENTITYMAP ) ;
 
-- Entity - POD_EntityMapRec 
CREATE TABLE POD_ENTITYMAPREC ( 
           ZKEY               INTEGER            NOT NULL , 
           SEQNR              INTEGER            NOT NULL , 
           FLDNAME            TEXT( 32 )                  , 
           FLDID              INTEGER                     , 
           FLDTYPE            TEXT( 1 )                   , 
           FLDLTH             INTEGER                     , 
           FLDOFFSET          INTEGER                     , 
           FK_ZKEY_POD_ENTITY INTEGER            NOT NULL , 
           FKZKEYTETABLRECDAT INTEGER                      ) ;
 
CREATE UNIQUE INDEX PODENTITYMAPRECIDPODENTITYMAPR 
       ON POD_ENTITYMAPREC ( 
           ZKEY ) ;
 
CREATE INDEX PODENTITYMAPRECFKZKEYPODENTT01 
       ON POD_ENTITYMAPREC ( 
           FK_ZKEY_POD_ENTITY ) ;
 
CREATE INDEX PODENTITYMAPRECFKZKEYTTBLRCD02 
       ON POD_ENTITYMAPREC ( 
           FKZKEYTETABLRECDAT ) ;
 
-- Entity - POD_RelLinkMapFld 
CREATE TABLE POD_RELLINKMAPFLD ( 
           ZKEY               INTEGER            NOT NULL , 
           SEQNR              INTEGER            NOT NULL , 
           SRCAT_RCNM         TEXT( 32 )                  , 
           SRCAT_FLNM         TEXT( 32 )                  , 
           FLDNAME            TEXT( 32 )                  , 
           FK_ZKEYPODATTRIBUT INTEGER            NOT NULL , 
           FKZKEYPODRELLINKMA INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX PODRELLINKMAPFLDIDPODRELLNKMPF 
       ON POD_RELLINKMAPFLD ( 
           ZKEY ) ;
 
CREATE INDEX PODRELLINKMAPFLDFKZKEYPDTTRB01 
       ON POD_RELLINKMAPFLD ( 
           FK_ZKEYPODATTRIBUT ) ;
 
CREATE INDEX PODRELLINKMAPFLDFKZKYPDRLLNK02 
       ON POD_RELLINKMAPFLD ( 
           FKZKEYPODRELLINKMA ) ;
 
-- Entity - POD_RelLinkMapRec 
CREATE TABLE POD_RELLINKMAPREC ( 
           ZKEY               INTEGER            NOT NULL , 
           OWNER_MEMB         TEXT( 1 )                   , 
           RECNAME            TEXT( 32 )                  , 
           RECID              INTEGER                     , 
           SETNAME1           TEXT( 32 )                  , 
           SETID1             INTEGER                     , 
           SETNAME2           TEXT( 32 )                  , 
           SETID2             INTEGER                     , 
           FKZKEYPODENTITYMAP INTEGER                     , 
           FK_ZKEY_POD_ENTITY INTEGER            NOT NULL , 
           FKZKEYTETABLRECDAT INTEGER                      ) ;
 
CREATE UNIQUE INDEX PODRELLINKMAPRECIDPODRELLINKMP 
       ON POD_RELLINKMAPREC ( 
           ZKEY ) ;
 
CREATE INDEX PODRELLINKMAPRECFKZKYPDNTTYM01 
       ON POD_RELLINKMAPREC ( 
           FKZKEYPODENTITYMAP ) ;
 
CREATE INDEX PODRELLINKMAPRECFKZKEYPODNTT02 
       ON POD_RELLINKMAPREC ( 
           FK_ZKEY_POD_ENTITY ) ;
 
CREATE INDEX PODRELLINKMAPRECFKZKYTTBLRCD03 
       ON POD_RELLINKMAPREC ( 
           FKZKEYTETABLRECDAT ) ;
 
-- Entity - PresEnvDef 
CREATE TABLE PRESENVDEF ( 
           ZKEY               INTEGER            NOT NULL , 
           CTRLFONTDEL        INTEGER                     , 
           z_DESC             MEMO                        , 
           NAME               TEXT( 33 )                  , 
           LASTCTRL           INTEGER                     , 
           LASTFONT           INTEGER                     , 
           FK_ZKEY_Z_METADEF  INTEGER                      ) ;
 
CREATE UNIQUE INDEX PRESENVDEF_ID_PRESENVDEF 
       ON PRESENVDEF ( 
           ZKEY ) ;
 
CREATE INDEX PRESENVDEF_FK_ZKEY_Z_METADEF01 
       ON PRESENVDEF ( 
           FK_ZKEY_Z_METADEF ) ;
 
-- Entity - PropertyDef 
CREATE TABLE PROPERTYDEF ( 
           ZKEY               INTEGER            NOT NULL , 
           TAG                INTEGER                     , 
           TYPE               INTEGER                     , 
           MODE               INTEGER                     , 
           FK_ZKEY_CONTROLDEF INTEGER                      ) ;
 
CREATE UNIQUE INDEX PROPERTYDEF_ZKEY 
       ON PROPERTYDEF ( 
           ZKEY ) ;
 
CREATE INDEX PROPERTYDEF_FK_ZKEYCONTROLDE01 
       ON PROPERTYDEF ( 
           FK_ZKEY_CONTROLDEF ) ;
 
-- Entity - RegularExpression 
CREATE TABLE REGULAREXPRESSION ( 
           ZKEY               INTEGER            NOT NULL , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_CONTEXT    INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX REGULAREXPRESSIONIDREGULARXPRS 
       ON REGULAREXPRESSION ( 
           ZKEY ) ;
 
CREATE INDEX REGULAREXPRESSIONFKZKEYCONTX01 
       ON REGULAREXPRESSION ( 
           FK_ZKEY_CONTEXT ) ;
 
-- Entity - Report 
CREATE TABLE REPORT ( 
           ZKEY               INTEGER            NOT NULL , 
           TAG                TEXT( 8 )                   , 
           z_DESC             MEMO                        , 
           SIRONNAME          TEXT( 8 )                   , 
           SUPPRSSEMPTYTXTFLD TEXT( 1 )                   , 
           UNIT               INTEGER                     , 
           FK_ZKEY_Z_METADEF  INTEGER                      ) ;
 
CREATE UNIQUE INDEX REPORT_ID_REPORT 
       ON REPORT ( 
           ZKEY ) ;
 
CREATE INDEX REPORT_FK_ZKEY_Z_METADEF01 
       ON REPORT ( 
           FK_ZKEY_Z_METADEF ) ;
 
-- Entity - RepositoryClient 
CREATE TABLE REPOSITORYCLIENT ( 
           ZKEY               INTEGER            NOT NULL , 
           WKS_ID             INTEGER                     , 
           MAXZKEY            INTEGER                     , 
           LASTSYNCZKEY       INTEGER                     , 
           z_DESC             MEMO                        , 
           DEFAULTLPLR_ZKEY   INTEGER                     , 
           FK_ZKEYINSTALLATIO INTEGER                      ) ;
 
CREATE UNIQUE INDEX REPOSITORYCLIENTIDREPOSITORYCL 
       ON REPOSITORYCLIENT ( 
           ZKEY ) ;
 
CREATE INDEX REPOSITORYCLIENTFKZKEYINSTLL01 
       ON REPOSITORYCLIENT ( 
           FK_ZKEYINSTALLATIO ) ;
 
-- Entity - RevEvent 
CREATE TABLE REVEVENT ( 
           TYPE               INTEGER            NOT NULL , 
           z_DESC             TEXT( 32 )         NOT NULL  ) ;
 
CREATE UNIQUE INDEX REVEVENT_ID 
       ON REVEVENT ( 
           TYPE ) ;
 
-- Entity - RevSubEvent 
CREATE TABLE REVSUBEVENT ( 
           z_DESC             TEXT( 254 )                 , 
           SUBTYPE            INTEGER            NOT NULL , 
           NECESSARY          TEXT( 1 )                   , 
           FK_TYPE_REVEVENT   INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX REVSUBEVENT_REVEVENT_HAS 
       ON REVSUBEVENT ( 
           FK_TYPE_REVEVENT, 
           SUBTYPE ) ;
 
CREATE INDEX REVSUBEVENT_FK_TYPE_REVEVENT01 
       ON REVSUBEVENT ( 
           FK_TYPE_REVEVENT ) ;
 
-- Entity - SA_Entity 
CREATE TABLE SA_ENTITY ( 
           ZKEY               INTEGER            NOT NULL , 
           ER_PORTFACTOR      INTEGER                     , 
           ER_DIAGRAMPOSX     INTEGER                     , 
           ER_DIAGRAMPOSY     INTEGER                     , 
           FK_ZKEY_ER_ENTITY  INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX SA_ENTITY_ID_SA_ENTITY 
       ON SA_ENTITY ( 
           ZKEY ) ;
 
CREATE INDEX SA_ENTITY_FK_ZKEY_ER_ENTITY01 
       ON SA_ENTITY ( 
           FK_ZKEY_ER_ENTITY ) ;
 
-- Entity - SA_RelType 
CREATE TABLE SA_RELTYPE ( 
           ZKEY               INTEGER            NOT NULL , 
           ER_DIAGRAMBENDPOSX INTEGER                     , 
           ER_DIAGRAMBENDPOSY INTEGER                     , 
           ER_DIAGRAME1POSX   INTEGER                     , 
           ER_DIAGRAME1POSY   INTEGER                     , 
           ER_DIAGRAME2POSX   INTEGER                     , 
           ER_DIAGRAME2POSY   INTEGER                     , 
           FK_ZKEY_ER_RELTYPE INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX SA_RELTYPE_ID_SA_RELTYPE 
       ON SA_RELTYPE ( 
           ZKEY ) ;
 
CREATE INDEX SA_RELTYPE_FK_ZKEY_ER_RELTYP01 
       ON SA_RELTYPE ( 
           FK_ZKEY_ER_RELTYPE ) ;
 
-- Entity - SironComment 
CREATE TABLE SIRONCOMMENT ( 
           ZKEY               INTEGER            NOT NULL , 
           z_TEXT             TEXT( 254 )                 , 
           z_NUMBER           INTEGER                     , 
           LENGTH             INTEGER                     , 
           AUTOSEQ            INTEGER                     , 
           AUTOSEQ02          INTEGER                     , 
           FK_ZKEYSIRONKATALO INTEGER                     , 
           FKZKEYORIGSIRONFIE INTEGER                      ) ;
 
CREATE UNIQUE INDEX SIRONCOMMENT_ZKEY 
       ON SIRONCOMMENT ( 
           ZKEY ) ;
 
CREATE INDEX SIRONCOMMENTFKZKEYSIRONKATAL01 
       ON SIRONCOMMENT ( 
           FK_ZKEYSIRONKATALO ) ;
 
CREATE INDEX SIRONCOMMENTFKZKEYORIGSIRONF02 
       ON SIRONCOMMENT ( 
           FKZKEYORIGSIRONFIE ) ;
 
-- Entity - SironKatalog 
CREATE TABLE SIRONKATALOG ( 
           ZKEY               INTEGER            NOT NULL , 
           NAME               TEXT( 8 )                   , 
           ORGFORM            TEXT( 16 )                  , 
           KEYATTRIBUTE       TEXT( 1 )                   , 
           RECLEN             INTEGER                     , 
           RECFORM            TEXT( 2 )                   , 
           DDNAME             TEXT( 8 )                   , 
           z_PASSWORD         TEXT( 8 )                   , 
           UPRONAME           TEXT( 8 )                   , 
           BLKLEN             INTEGER                     , 
           KEYLEN             INTEGER                     , 
           KEYPOS             INTEGER                     , 
           FKZKEYTETABLRECDAT INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX SIRONKATALOG_ZKEY 
       ON SIRONKATALOG ( 
           ZKEY ) ;
 
CREATE INDEX SIRONKATALOGFKZKEYTETABLRECD01 
       ON SIRONKATALOG ( 
           FKZKEYTETABLRECDAT ) ;
 
-- Entity - SourceFile 
CREATE TABLE SOURCEFILE ( 
           ZKEY               INTEGER            NOT NULL , 
           NAME               TEXT( 8 )          NOT NULL , 
           z_DESC             MEMO                        , 
           EXTENSION          TEXT( 3 )                   , 
           CM_MANAGED         TEXT( 1 )                   , 
           OWNERTYPE          TEXT( 1 )                   , 
           LANGUAGETYPE       TEXT( 1 )                   , 
           SUBDIRECTORY       TEXT( 32 )                  , 
           DOMANANDGLBLOPGRPN TEXT( 8 )                   , 
           AUTOSEQ            INTEGER                     , 
           AUTOSEQ02          INTEGER                     , 
           FK_ZKEY_Z_METADEF  INTEGER                     , 
           FKZKEYEXECCOMPOSIT INTEGER                     , 
           FK_ZKEY_LOD        INTEGER                     , 
           FK_ZKEY_DIALOG     INTEGER                     , 
           FK_ZKEY_PRESENVDEF INTEGER                      ) ;
 
CREATE UNIQUE INDEX SOURCEFILE_ID_VML_SOURCE 
       ON SOURCEFILE ( 
           ZKEY ) ;
 
CREATE INDEX SOURCEFILE_FK_ZKEY_Z_METADEF01 
       ON SOURCEFILE ( 
           FK_ZKEY_Z_METADEF ) ;
 
CREATE INDEX SOURCEFILE_FKZKEYEXECCOMPOSI02 
       ON SOURCEFILE ( 
           FKZKEYEXECCOMPOSIT ) ;
 
CREATE INDEX SOURCEFILE_FK_ZKEY_LOD03 
       ON SOURCEFILE ( 
           FK_ZKEY_LOD ) ;
 
CREATE INDEX SOURCEFILE_FK_ZKEY_DIALOG04 
       ON SOURCEFILE ( 
           FK_ZKEY_DIALOG ) ;
 
CREATE INDEX SOURCEFILE_FK_ZKEY_PRESENVDE05 
       ON SOURCEFILE ( 
           FK_ZKEY_PRESENVDEF ) ;
 
-- Entity - SubjectArea 
CREATE TABLE SUBJECTAREA ( 
           NAME               TEXT( 32 )         NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           z_DESC             MEMO                        , 
           UPDATEAUTH         TEXT( 1 )                   , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_ENTPERMODE INTEGER            NOT NULL , 
           FK_ZKEY_Z_METADEF  INTEGER                      ) ;
 
CREATE UNIQUE INDEX SUBJECTAREA_ID_SUBJECTAREA 
       ON SUBJECTAREA ( 
           ZKEY ) ;
 
CREATE INDEX SUBJECTAREA_FK_ZKEYENTPERMOD01 
       ON SUBJECTAREA ( 
           FK_ZKEY_ENTPERMODE ) ;
 
CREATE INDEX SUBJECTAREA_FK_ZKEY_Z_METADE02 
       ON SUBJECTAREA ( 
           FK_ZKEY_Z_METADEF ) ;
 
-- Entity - SysEnqueue 
CREATE TABLE SYSENQUEUE ( 
           z_TIMESTAMP        TEXT( 25 )         NOT NULL , 
           USERNAME           TEXT( 32 )         NOT NULL , 
           USERDESC           MEMO                         ) ;
 
CREATE UNIQUE INDEX SYSENQUEUE_USERNAME 
       ON SYSENQUEUE ( 
           USERNAME ) ;
 
-- Entity - TableEntry 
CREATE TABLE TABLEENTRY ( 
           ZKEY               INTEGER            NOT NULL , 
           EXTERNALVALUE      TEXT( 254 )                 , 
           INTERNALVALUE      TEXT( 254 )                 , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_CONTEXT    INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX TABLEENTRY_ID_TABLEENTRY 
       ON TABLEENTRY ( 
           ZKEY ) ;
 
CREATE INDEX TABLEENTRY_FK_ZKEY_CONTEXT01 
       ON TABLEENTRY ( 
           FK_ZKEY_CONTEXT ) ;
 
-- Entity - TE_DB_Environ 
CREATE TABLE TE_DB_ENVIRON ( 
           NAME               TEXT( 32 )         NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           PARADIGM           TEXT( 1 )                   , 
           z_DESC             MEMO                        , 
           TYPE               TEXT( 1 )                   , 
           FK_ZKEY_SUBJECTARE INTEGER                     , 
           FK_ZKEY_Z_METADEF  INTEGER                      ) ;
 
CREATE UNIQUE INDEX TE_DB_ENVIRON_ID_TE_DB_ENVIRON 
       ON TE_DB_ENVIRON ( 
           ZKEY ) ;
 
CREATE INDEX TE_DB_ENVIRONFKZKEYSUBJECTAR01 
       ON TE_DB_ENVIRON ( 
           FK_ZKEY_SUBJECTARE ) ;
 
CREATE INDEX TE_DB_ENVIRON_FK_ZKEYZMETADE02 
       ON TE_DB_ENVIRON ( 
           FK_ZKEY_Z_METADEF ) ;
 
-- Entity - TE_DBMS_Source 
CREATE TABLE TE_DBMS_SOURCE ( 
           NAME               TEXT( 32 )         NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           MAXFIXEDATTRLTH    INTEGER                     , 
           OVERFLOWATTRLTH    INTEGER                     , 
           z_DESC             MEMO                        , 
           PARADIGM           TEXT( 1 )                   , 
           DBMS               TEXT( 30 )                  , 
           GENERATEEXECUTABLE TEXT( 8 )                   , 
           EXECUTABLE         TEXT( 8 )                   , 
           GENKEYEXECUTABLE   TEXT( 32 )                  , 
           CONECTIONTYPE      TEXT( 1 )                   , 
           SIRONDB_TYPE       TEXT( 1 )                   , 
           SIRONDB_SUBTYPE    TEXT( 1 )                   , 
           DEFAULTOWNER       TEXT( 32 )                  , 
           DISPLAYOWNER       TEXT( 1 )                   , 
           DISPLAYDBMS_ID     TEXT( 1 )                   , 
           NETWORK            TEXT( 8 )                   , 
           DBH_DATA           LONGBINARY                  , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_TEDBENVIRO INTEGER                      ) ;
 
CREATE UNIQUE INDEX TE_DBMS_SOURCE_ID_TE_DBMSSOURC 
       ON TE_DBMS_SOURCE ( 
           ZKEY ) ;
 
CREATE INDEX TE_DBMSSOURCEFKZKEYTEDBENVIR01 
       ON TE_DBMS_SOURCE ( 
           FK_ZKEY_TEDBENVIRO ) ;
 
-- Entity - TE_FieldDataRel 
CREATE TABLE TE_FIELDDATAREL ( 
           NAME               TEXT( 32 )         NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           z_DESC             MEMO                        , 
           DATAORRELFIELDORSE TEXT( 1 )                   , 
           z_KEY              TEXT( 1 )                   , 
           DBMS_ID            INTEGER                     , 
           DATATYPE           TEXT( 8 )                   , 
           LENGTH             INTEGER                     , 
           OFFSET             INTEGER                     , 
           SQL_SCALE          INTEGER                     , 
           SQL_NULLS          TEXT( 1 )                   , 
           SQL_LABEL          TEXT( 30 )                  , 
           SQL_REMARKS        TEXT( 254 )                 , 
           AUTOSEQ            INTEGER                     , 
           AUTOSEQ02          INTEGER                     , 
           FKZKEYORIGSIRONFIE INTEGER                     , 
           FKZKEYTEFIELDDATAR INTEGER                     , 
           FK_ZKEY_ERATTRIBUT INTEGER                     , 
           FK_ZKEY_ER_RELLINK INTEGER                     , 
           FKZKEYPODENTITYMAP INTEGER                     , 
           FKZKEYTETABLRECDAT INTEGER            NOT NULL , 
           FKZKEYPODRELLINKMA INTEGER                     , 
           FKZKEYTEPHYSICALDA INTEGER                      ) ;
 
CREATE UNIQUE INDEX TE_FIELDDATARELIDTEFIELDDATARE 
       ON TE_FIELDDATAREL ( 
           ZKEY ) ;
 
CREATE INDEX TEFIELDDATARELFKZKEYORIGSIRN01 
       ON TE_FIELDDATAREL ( 
           FKZKEYORIGSIRONFIE ) ;
 
CREATE INDEX TEFIELDDATARELFKZKEYTEFILDDT02 
       ON TE_FIELDDATAREL ( 
           FKZKEYTEFIELDDATAR ) ;
 
CREATE INDEX TEFIELDDATARELFKZKEYERATTRIB03 
       ON TE_FIELDDATAREL ( 
           FK_ZKEY_ERATTRIBUT ) ;
 
CREATE INDEX TEFIELDDATARELFKZKEYERRELLIN04 
       ON TE_FIELDDATAREL ( 
           FK_ZKEY_ER_RELLINK ) ;
 
CREATE INDEX TEFIELDDATARELFKZKEYPODNTTYM05 
       ON TE_FIELDDATAREL ( 
           FKZKEYPODENTITYMAP ) ;
 
CREATE INDEX TEFIELDDATARELFKZKEYTETBLRCD06 
       ON TE_FIELDDATAREL ( 
           FKZKEYTETABLRECDAT ) ;
 
CREATE INDEX TEFIELDDATARELFKZKEYPODRLLNK07 
       ON TE_FIELDDATAREL ( 
           FKZKEYPODRELLINKMA ) ;
 
CREATE INDEX TEFIELDDATARELFKZKEYTEPHYSCL08 
       ON TE_FIELDDATAREL ( 
           FKZKEYTEPHYSICALDA ) ;
 
-- Entity - TE_PhysicalDataType 
CREATE TABLE TE_PHYSICALDATATYPE ( 
           ZKEY               INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX TEPHYSICALDATATYPEIDTEPHYSCLTY 
       ON TE_PHYSICALDATATYPE ( 
           ZKEY ) ;
 
-- Entity - TE_TablRecDataRel 
CREATE TABLE TE_TABLRECDATAREL ( 
           NAME               TEXT( 32 )         NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           DATAORREL          TEXT( 1 )                   , 
           DBMS_ID            INTEGER                     , 
           SQL_TABLEOWNER     TEXT( 32 )                  , 
           SQL_TABLEQUAL      TEXT( 32 )                  , 
           z_DESC             MEMO                        , 
           AUTOSEQ            INTEGER                     , 
           FKZKEYORIGSIRONFIE INTEGER                     , 
           FK_ZKEY_ER_RELTYPE INTEGER                     , 
           FK_ZKEYTEDBMSSOURC INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX TETABLRECDATARELIDTETABLRECDAT 
       ON TE_TABLRECDATAREL ( 
           ZKEY ) ;
 
CREATE INDEX TETABLRECDATARELFKZKEYORGSRN01 
       ON TE_TABLRECDATAREL ( 
           FKZKEYORIGSIRONFIE ) ;
 
CREATE INDEX TETABLRECDATARELFKZKEYERRLTY02 
       ON TE_TABLRECDATAREL ( 
           FK_ZKEY_ER_RELTYPE ) ;
 
CREATE INDEX TETABLRECDATARELFKZKYTDBMSSR03 
       ON TE_TABLRECDATAREL ( 
           FK_ZKEYTEDBMSSOURC ) ;
 
-- Entity - TE_TablRecKey 
CREATE TABLE TE_TABLRECKEY ( 
           NAME               TEXT( 32 )         NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           CATEGORY           TEXT( 1 )                   , 
           z_DESC             MEMO                        , 
           INDEXNAME          TEXT( 32 )                  , 
           AUTOSEQ            INTEGER                     , 
           AUTOSEQ02          INTEGER                     , 
           FKZKEYTETABLRECDAT INTEGER                     , 
           FKZKEYERENTIDENTIF INTEGER                      ) ;
 
CREATE UNIQUE INDEX TE_TABLRECKEY_ZKEY 
       ON TE_TABLRECKEY ( 
           ZKEY ) ;
 
CREATE INDEX TETABLRECKEYFKZKEYTETABLRECD01 
       ON TE_TABLRECKEY ( 
           FKZKEYTETABLRECDAT ) ;
 
CREATE INDEX TETABLRECKEYFKZKEYERENTIDENT02 
       ON TE_TABLRECKEY ( 
           FKZKEYERENTIDENTIF ) ;
 
-- Entity - UI_Spec 
CREATE TABLE UI_SPEC ( 
           ZKEY               INTEGER            NOT NULL , 
           NAME               TEXT( 8 )                   , 
           ACTIONTYPE         TEXT( 1 )                   , 
           LISTSELECT         TEXT( 1 )                   , 
           LISTALLTEXT        TEXT( 50 )                  , 
           LISTQUALIFYTEXT    TEXT( 50 )                  , 
           WDOD_STYLE         TEXT( 1 )                   , 
           LISTTYPE           TEXT( 1 )                   , 
           TRANSFEROBJECTNAME TEXT( 32 )                  , 
           TRANSFERQUALIFIER  TEXT( 254 )                 , 
           EXITTEXT           TEXT( 50 )                  , 
           LOADTEXT           TEXT( 50 )                  , 
           ACTIONBARTEXT      TEXT( 50 )                  , 
           SELECTQUALIFIER    TEXT( 254 )                 , 
           EXITMENUTEXT       TEXT( 50 )                  , 
           SELECTTEXT         TEXT( 50 )                  , 
           SELECTMENUTEXT     TEXT( 50 )                  , 
           LISTMENUTEXT       TEXT( 50 )                  , 
           STYLEOBJECTTYPE    TEXT( 1 )                   , 
           z_DESC             MEMO                        , 
           FK_ZKEY_Z_METADEF  INTEGER                     , 
           FKZKEYWNDDESIGNSPE INTEGER            NOT NULL , 
           FK_ZKEY_UIS_ENTITY INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX UI_SPEC_ID_UI_SPEC 
       ON UI_SPEC ( 
           ZKEY ) ;
 
CREATE INDEX UI_SPEC_FK_ZKEY_Z_METADEF01 
       ON UI_SPEC ( 
           FK_ZKEY_Z_METADEF ) ;
 
CREATE INDEX UI_SPEC_FKZKEYWNDDESIGNSPE02 
       ON UI_SPEC ( 
           FKZKEYWNDDESIGNSPE ) ;
 
CREATE INDEX UI_SPEC_FK_ZKEY_UIS_ENTITY03 
       ON UI_SPEC ( 
           FK_ZKEY_UIS_ENTITY ) ;
 
-- Entity - UIS_Entity 
CREATE TABLE UIS_ENTITY ( 
           ZKEY               INTEGER            NOT NULL , 
           ELIMINATEWND       TEXT( 1 )                   , 
           SEQNO              INTEGER                     , 
           LISTTYPEFLAG       TEXT( 1 )                   , 
           REPORTORIENTATINFL TEXT( 1 )                   , 
           REPORTGROUPBORDER  TEXT( 1 )                   , 
           VERTICALCONTROLSIZ INTEGER                     , 
           HORIZONTALCONTROLS INTEGER                     , 
           VERTICLSPCNGINCRMN INTEGER                     , 
           AUTODESIGNCASETYPE TEXT( 2 )                   , 
           FIRSTDATAFIELDNAME TEXT( 10 )                  , 
           ROOTONLYLIST       TEXT( 1 )                   , 
           HEADERTEXT         TEXT( 254 )                 , 
           FOOTERTEXT         TEXT( 254 )                 , 
           FORCEHEADERPERENTT TEXT( 1 )                   , 
           FONTSIZE           INTEGER                     , 
           BOLDFLAG           TEXT( 1 )                   , 
           ITALICFLAG         TEXT( 1 )                   , 
           HEADERFONTSIZE     INTEGER                     , 
           HEADERBOLDFLAG     TEXT( 1 )                   , 
           HEADERITALICFLAG   TEXT( 1 )                   , 
           FOOTERFONTSIZE     INTEGER                     , 
           FOOTERBOLDFLAG     TEXT( 1 )                   , 
           FOOTERITALICFLAG   TEXT( 1 )                   , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_LOD_ENTITY INTEGER                     , 
           FK_ZKEY_UIS_ENTITY INTEGER                      ) ;
 
CREATE UNIQUE INDEX UIS_ENTITY_ID_UIS_ENTITY 
       ON UIS_ENTITY ( 
           ZKEY ) ;
 
CREATE INDEX UIS_ENTITY_FK_ZKEY_LOD_ENTIT01 
       ON UIS_ENTITY ( 
           FK_ZKEY_LOD_ENTITY ) ;
 
CREATE INDEX UIS_ENTITY_FK_ZKEY_UIS_ENTIT02 
       ON UIS_ENTITY ( 
           FK_ZKEY_UIS_ENTITY ) ;
 
-- Entity - UIS_Include 
CREATE TABLE UIS_INCLUDE ( 
           ZKEY               INTEGER            NOT NULL , 
           SUBOBJECTTYPE      TEXT( 1 )                   , 
           SUBOBJECTNAME      TEXT( 32 )                  , 
           SUBOBJECTLISTQUAL  TEXT( 254 )                 , 
           SUBOBJECTTRANSQUAL TEXT( 254 )                 , 
           SUBOBJECTOPERATORS TEXT( 2 )                   , 
           FK_ZKEY_VIEWOBJREF INTEGER                     , 
           FK_ZKEY_UIS_ENTITY INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX UIS_INCLUDE_ID_UIS_INCLUDE 
       ON UIS_INCLUDE ( 
           ZKEY ) ;
 
CREATE INDEX UIS_INCLUDE_FK_ZKEYVIEWOBJRE01 
       ON UIS_INCLUDE ( 
           FK_ZKEY_VIEWOBJREF ) ;
 
CREATE INDEX UIS_INCLUDE_FK_ZKEY_UISENTIT02 
       ON UIS_INCLUDE ( 
           FK_ZKEY_UIS_ENTITY ) ;
 
-- Entity - UIS_QualList 
CREATE TABLE UIS_QUALLIST ( 
           ZKEY               INTEGER            NOT NULL , 
           QUALATTRIBZKEY     INTEGER                     , 
           QUALIFIERATTRIB    TEXT( 32 )                  , 
           z_JOIN             TEXT( 3 )                   , 
           OPERATOR           TEXT( 2 )                   , 
           SEQNO              INTEGER                     , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_UI_SPEC    INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX UIS_QUALLIST_ID_UIS_QUALLIST 
       ON UIS_QUALLIST ( 
           ZKEY ) ;
 
CREATE INDEX UIS_QUALLIST_FK_ZKEY_UI_SPEC01 
       ON UIS_QUALLIST ( 
           FK_ZKEY_UI_SPEC ) ;
 
-- Entity - UIS_Tab 
CREATE TABLE UIS_TAB ( 
           ZKEY               INTEGER            NOT NULL , 
           TITLE              TEXT( 50 )                  , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_UIS_ENTITY INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX UIS_TAB_ZKEY 
       ON UIS_TAB ( 
           ZKEY ) ;
 
CREATE INDEX UIS_TAB_FK_ZKEY_UIS_ENTITY01 
       ON UIS_TAB ( 
           FK_ZKEY_UIS_ENTITY ) ;
 
-- Entity - User 
CREATE TABLE z_USER ( 
           NAME               TEXT( 32 )         NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           z_PASSWORD         TEXT( 8 )                   , 
           z_DESC             MEMO                         ) ;
 
CREATE UNIQUE INDEX z_USER_ID_USER 
       ON z_USER ( 
           ZKEY ) ;
 
-- Entity - UserMetaStatus 
CREATE TABLE USERMETASTATUS ( 
           ZKEY               INTEGER            NOT NULL , 
           STATUS             INTEGER            NOT NULL , 
           CHECKOUTDATE       TEXT( 25 )         NOT NULL , 
           COMMENTS           TEXT( 254 )                 , 
           FK_ZKEY_LPLR       INTEGER            NOT NULL , 
           FKZKEYREPOSITORYCL INTEGER                     , 
           FK_ZKEY_Z_USER     INTEGER            NOT NULL , 
           FK_ZKEY_Z_METADEF  INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX USERMETASTATUS_IDUSERMETASTATU 
       ON USERMETASTATUS ( 
           ZKEY ) ;
 
CREATE INDEX USERMETASTATUS_FK_ZKEY_LPLR01 
       ON USERMETASTATUS ( 
           FK_ZKEY_LPLR ) ;
 
CREATE INDEX USERMETASTATUSFKZKEYREPSTRYC02 
       ON USERMETASTATUS ( 
           FKZKEYREPOSITORYCL ) ;
 
CREATE INDEX USERMETASTATUS_FK_ZKEY_Z_USE03 
       ON USERMETASTATUS ( 
           FK_ZKEY_Z_USER ) ;
 
CREATE INDEX USERMETASTATUS_FKZKEYZMETADE04 
       ON USERMETASTATUS ( 
           FK_ZKEY_Z_METADEF ) ;
 
-- Entity - ViewObjRef 
CREATE TABLE VIEWOBJREF ( 
           ZKEY               INTEGER            NOT NULL , 
           NAME               TEXT( 32 )                  , 
           z_DESC             MEMO                        , 
           z_LEVEL            INTEGER                     , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_UIS_INCLUD INTEGER                     , 
           FK_ZKEY_UI_SPEC    INTEGER                     , 
           FK_ZKEY_Z_METADEF  INTEGER                     , 
           FK_ZKEY_LOD        INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX VIEWOBJREF_ID_VIEWOBJREF 
       ON VIEWOBJREF ( 
           ZKEY ) ;
 
CREATE INDEX VIEWOBJREF_FK_ZKEY_UIS_INCLU01 
       ON VIEWOBJREF ( 
           FK_ZKEY_UIS_INCLUD ) ;
 
CREATE INDEX VIEWOBJREF_FK_ZKEY_UI_SPEC02 
       ON VIEWOBJREF ( 
           FK_ZKEY_UI_SPEC ) ;
 
CREATE INDEX VIEWOBJREF_FK_ZKEY_Z_METADEF03 
       ON VIEWOBJREF ( 
           FK_ZKEY_Z_METADEF ) ;
 
CREATE INDEX VIEWOBJREF_FK_ZKEY_LOD04 
       ON VIEWOBJREF ( 
           FK_ZKEY_LOD ) ;
 
-- Entity - Window 
CREATE TABLE WINDOW ( 
           TAG                TEXT( 32 )                  , 
           SUBTYPE            INTEGER                     , 
           CAPTION            TEXT( 64 )                  , 
           PSDLG_X            INTEGER                     , 
           PSDLG_Y            INTEGER                     , 
           SZDLG_X            INTEGER                     , 
           SZDLG_Y            INTEGER                     , 
           DFLTBUTTON         TEXT( 32 )                  , 
           ZKEY               INTEGER            NOT NULL , 
           RESOURCEID         INTEGER                     , 
           DIL_ACTIVE         TEXT( 1 )                   , 
           PROFILEVIEW        TEXT( 32 )                  , 
           GENERALFLAG        INTEGER                     , 
           WINDOWBOI          LONGBINARY                  , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEYPHYSOVERRID INTEGER                     , 
           FK_ZKEY_WINDOWSTYL INTEGER            NOT NULL , 
           FK_ZKEY_DIALOG     INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX WINDOW_ID_WINDOW 
       ON WINDOW ( 
           ZKEY ) ;
 
CREATE INDEX WINDOW_FK_ZKEYPHYSOVERRID01 
       ON WINDOW ( 
           FK_ZKEYPHYSOVERRID ) ;
 
CREATE INDEX WINDOW_FK_ZKEY_WINDOWSTYL02 
       ON WINDOW ( 
           FK_ZKEY_WINDOWSTYL ) ;
 
CREATE INDEX WINDOW_FK_ZKEY_DIALOG03 
       ON WINDOW ( 
           FK_ZKEY_DIALOG ) ;
 
-- Entity - WindowStyle 
CREATE TABLE WINDOWSTYLE ( 
           ZKEY               INTEGER            NOT NULL , 
           TAG                TEXT( 32 )                  , 
           z_DESC             MEMO                        , 
           STYLE              INTEGER                     , 
           STYLEEX            INTEGER                     , 
           FK_ZKEY_PRESENVDEF INTEGER                      ) ;
 
CREATE UNIQUE INDEX WINDOWSTYLE_ZKEY 
       ON WINDOWSTYLE ( 
           ZKEY ) ;
 
CREATE INDEX WINDOWSTYLE_FK_ZKEYPRESENVDE01 
       ON WINDOWSTYLE ( 
           FK_ZKEY_PRESENVDEF ) ;
 
-- Entity - WndDesignSpec 
CREATE TABLE WNDDESIGNSPEC ( 
           ZKEY               INTEGER            NOT NULL , 
           ENTITYFROMSUBOBJ   TEXT( 1 )                   , 
           AUTOVERSION        TEXT( 1 )                   , 
           ACTIONTYPE         TEXT( 1 )                   , 
           USAGESTYLE         TEXT( 1 )                   , 
           z_CASCADE          TEXT( 1 )                   , 
           UPDATECANCELACTION TEXT( 1 )                   , 
           UPDATEDELETEACTION TEXT( 1 )                   , 
           UPDATESAVEACTION   TEXT( 1 )                   , 
           UPDATENEXTACTION   TEXT( 1 )                   , 
           UPDATEPREVACTION   TEXT( 1 )                   , 
           UPDATECREATEACTION TEXT( 1 )                   , 
           UPDATESAVETEXT     TEXT( 50 )                  , 
           UPDATECANCELTEXT   TEXT( 50 )                  , 
           UPDATEDELETETEXT   TEXT( 50 )                  , 
           UPDATENEXTTEXT     TEXT( 50 )                  , 
           UPDATEPREVTEXT     TEXT( 50 )                  , 
           UPDATESAVEACCEL    TEXT( 1 )                   , 
           UPDATECANCELACCEL  TEXT( 1 )                   , 
           UPDATEDELETEACCEL  TEXT( 1 )                   , 
           UPDATENEXTACCEL    TEXT( 1 )                   , 
           UPDATEPREVACCEL    TEXT( 1 )                   , 
           LISTOPTIONPOSITION TEXT( 1 )                   , 
           LISTUPDATEACTION   TEXT( 50 )                  , 
           LISTACTIONMENUTEXT TEXT( 50 )                  , 
           LISTACTIONACCEL    TEXT( 1 )                   , 
           LISTDELETEACTION   TEXT( 1 )                   , 
           LISTCREATEACTION   TEXT( 1 )                   , 
           CREATEFROMNEWIND   TEXT( 1 )                   , 
           LISTDELETETEXT     TEXT( 50 )                  , 
           LISTCREATETEXT     TEXT( 50 )                  , 
           LISTUPDATETEXT     TEXT( 50 )                  , 
           LISTNEWINDTEXT     TEXT( 50 )                  , 
           LISTDELETEACCEL    TEXT( 1 )                   , 
           LISTCREATEACCEL    TEXT( 1 )                   , 
           LISTUPDATEACCEL    TEXT( 1 )                   , 
           LISTTRIGGERMENUTXT TEXT( 50 )                  , 
           LISTTRIGGERTEXT    TEXT( 50 )                  , 
           LISTGROUPBOXTEXT   TEXT( 50 )                  , 
           UPDTACTIONMENUTXT  TEXT( 50 )                  , 
           WNDSTYLE           TEXT( 32 )                  , 
           WNDNAME            TEXT( 8 )                   , 
           WNDCAPTION         TEXT( 50 )                  , 
           WNDCAPTION2        TEXT( 50 )                  , 
           WNDNOMAP           TEXT( 1 )                   , 
           WNDREFRESH         TEXT( 1 )                   , 
           WNDSIZE_Y          INTEGER                     , 
           WNDSIZE_X          INTEGER                     , 
           WNDSTART_Y         INTEGER                     , 
           WNDSTART_X         INTEGER                     , 
           WNDDIL_MESSAGE     TEXT( 1 )                   , 
           FULLWND            TEXT( 1 )                   , 
           FK_ZKEY_WINDOWSTYL INTEGER                     , 
           FK_ZKEY_UIS_ENTITY INTEGER                      ) ;
 
CREATE UNIQUE INDEX WNDDESIGNSPEC_ID_WNDDESIGNSPEC 
       ON WNDDESIGNSPEC ( 
           ZKEY ) ;
 
CREATE INDEX WNDDESIGNSPECFKZKEYWINDOWSTY01 
       ON WNDDESIGNSPEC ( 
           FK_ZKEY_WINDOWSTYL ) ;
 
CREATE INDEX WNDDESIGNSPEC_FKZKEYUISENTIT02 
       ON WNDDESIGNSPEC ( 
           FK_ZKEY_UIS_ENTITY ) ;
 
-- Entity - WndEvent 
CREATE TABLE WNDEVENT ( 
           TYPE               INTEGER                     , 
           ACCELERATOR        TEXT( 32 )                  , 
           ZKEY               INTEGER            NOT NULL , 
           AUTOSEQ            INTEGER                     , 
           FK_ZKEY_WINDOW     INTEGER            NOT NULL , 
           FK_ZKEY_Z_ACTION   INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX WNDEVENT_ID_WNDEVENT 
       ON WNDEVENT ( 
           ZKEY ) ;
 
CREATE INDEX WNDEVENT_FK_ZKEY_WINDOW01 
       ON WNDEVENT ( 
           FK_ZKEY_WINDOW ) ;
 
CREATE INDEX WNDEVENT_FK_ZKEY_Z_ACTION02 
       ON WNDEVENT ( 
           FK_ZKEY_Z_ACTION ) ;
 
-- Entity - Z_MetaDef 
CREATE TABLE Z_METADEF ( 
           NAME               TEXT( 32 )         NOT NULL , 
           ZKEY               INTEGER            NOT NULL , 
           TYPE               INTEGER            NOT NULL , 
           LASTUPDATEDATE     TEXT( 25 )                  , 
           LASTCHECKINDATE    TEXT( 25 )                  , 
           z_DESC             MEMO                        , 
           AUTOSEQ            INTEGER                     , 
           AUTOSEQ02          INTEGER                     , 
           FK_ZKEY_CPLR       INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX Z_METADEF_ID_Z_METADEF 
       ON Z_METADEF ( 
           ZKEY ) ;
 
CREATE INDEX Z_METADEF_FK_ZKEY_CPLR01 
       ON Z_METADEF ( 
           FK_ZKEY_CPLR ) ;
 
CREATE TABLE MM_UIS_TAB_FOR_LOD_ATTRIBUTE ( 
           FK_ZKEYLODATTRIBUT INTEGER            NOT NULL , 
           FK_ZKEY_UIS_TAB    INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMUISTABFORLODATTRBTDMMSTBFRLD 
       ON MM_UIS_TAB_FOR_LOD_ATTRIBUTE ( 
           FK_ZKEYLODATTRIBUT, 
           FK_ZKEY_UIS_TAB ) ;
 
CREATE INDEX MMUISTABFRLDTTRBTFKZKYLDTTRB01 
       ON MM_UIS_TAB_FOR_LOD_ATTRIBUTE ( 
           FK_ZKEYLODATTRIBUT ) ;
 
CREATE INDEX MMUISTABFORLODATTRIBTFKZKYST02 
       ON MM_UIS_TAB_FOR_LOD_ATTRIBUTE ( 
           FK_ZKEY_UIS_TAB ) ;
 
CREATE TABLE MMTETABLRECDATARELSDNTEDBENVIR ( 
           FK_ZKEY_TEDBENVIRO INTEGER            NOT NULL , 
           FKZKEYTETABLRECDAT INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMTTBLRCDTRLSDNTDBNVRDMMTTBLRC 
       ON MMTETABLRECDATARELSDNTEDBENVIR ( 
           FK_ZKEY_TEDBENVIRO, 
           FKZKEYTETABLRECDAT ) ;
 
CREATE INDEX MMTTBLRCDTRLSDNTDBNVRFKZKYTD01 
       ON MMTETABLRECDATARELSDNTEDBENVIR ( 
           FK_ZKEY_TEDBENVIRO ) ;
 
CREATE INDEX MMTTBLRCDTRLSDNTDBNVRFKZKYTT02 
       ON MMTETABLRECDATARELSDNTEDBENVIR ( 
           FKZKEYTETABLRECDAT ) ;
 
CREATE TABLE MM_VIEWOBJREF_FOR_REPORT ( 
           FK_ZKEY_REPORT     INTEGER            NOT NULL , 
           FK_ZKEY_VIEWOBJREF INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMVIEWOBJREFFORRPRTDMMVWBJRFFR 
       ON MM_VIEWOBJREF_FOR_REPORT ( 
           FK_ZKEY_REPORT, 
           FK_ZKEY_VIEWOBJREF ) ;
 
CREATE INDEX MMVIEWOBJREFFORREPRTFKZKYRPR01 
       ON MM_VIEWOBJREF_FOR_REPORT ( 
           FK_ZKEY_REPORT ) ;
 
CREATE INDEX MMVIEWOBJREFFRRPRTFKZKYVWBJR02 
       ON MM_VIEWOBJREF_FOR_REPORT ( 
           FK_ZKEY_VIEWOBJREF ) ;
 
CREATE TABLE MMAPPLICATIONSXCTBLBYREPOSITOR ( 
           FKZKEYREPOSITORYCL INTEGER            NOT NULL , 
           FK_ZKEY_APPLICATIO INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMPPLCTNSXCTBLBYRPSTRDMMPPLCTN 
       ON MMAPPLICATIONSXCTBLBYREPOSITOR ( 
           FKZKEYREPOSITORYCL, 
           FK_ZKEY_APPLICATIO ) ;
 
CREATE INDEX MMPPLCTNSXCTBLBYRPSTRFKZKYRP01 
       ON MMAPPLICATIONSXCTBLBYREPOSITOR ( 
           FKZKEYREPOSITORYCL ) ;
 
CREATE INDEX MMPPLCTNSXCTBLBYRPSTRFKZKYPP02 
       ON MMAPPLICATIONSXCTBLBYREPOSITOR ( 
           FK_ZKEY_APPLICATIO ) ;
 
CREATE TABLE MM_UI_SPEC_HAS_VIEWOBJREF ( 
           FK_ZKEY_VIEWOBJREF INTEGER            NOT NULL , 
           FK_ZKEY_UI_SPEC    INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMUISPECHASVIEWOBJREFDMMSPCHSV 
       ON MM_UI_SPEC_HAS_VIEWOBJREF ( 
           FK_ZKEY_VIEWOBJREF, 
           FK_ZKEY_UI_SPEC ) ;
 
CREATE INDEX MMUISPECHASVIWBJRFFKZKYVWBJR01 
       ON MM_UI_SPEC_HAS_VIEWOBJREF ( 
           FK_ZKEY_VIEWOBJREF ) ;
 
CREATE INDEX MMUISPECHASVIEWOBJREFFKZKYSP02 
       ON MM_UI_SPEC_HAS_VIEWOBJREF ( 
           FK_ZKEY_UI_SPEC ) ;
 
CREATE TABLE MM_CONTROLDEF_HASMSSG_OPERATIO ( 
           FK_ZKEY_OPERATION  INTEGER            NOT NULL , 
           FK_ZKEY_CONTROLDEF INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMCNTRLDFHSMSSGPRTDMMCNTRLDFHS 
       ON MM_CONTROLDEF_HASMSSG_OPERATIO ( 
           FK_ZKEY_OPERATION, 
           FK_ZKEY_CONTROLDEF ) ;
 
CREATE INDEX MMCONTROLDFHSMSSGPRTFKZKYPRT01 
       ON MM_CONTROLDEF_HASMSSG_OPERATIO ( 
           FK_ZKEY_OPERATION ) ;
 
CREATE INDEX MMCNTRLDFHSMSSGPRTFKZKYCNTRL02 
       ON MM_CONTROLDEF_HASMSSG_OPERATIO ( 
           FK_ZKEY_CONTROLDEF ) ;
 
CREATE TABLE MM_TE_TABLRECKEYSTEFIELDDATARE ( 
           FKZKEYTEFIELDDATAR INTEGER            NOT NULL , 
           FK_ZKEYTETABLRECKE INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMTTBLRCKYSTFLDDTRDMMTTBLRCKYS 
       ON MM_TE_TABLRECKEYSTEFIELDDATARE ( 
           FKZKEYTEFIELDDATAR, 
           FK_ZKEYTETABLRECKE ) ;
 
CREATE INDEX MMTTBLRCKYSTFLDDTRFKZKYTFLDD01 
       ON MM_TE_TABLRECKEYSTEFIELDDATARE ( 
           FKZKEYTEFIELDDATAR ) ;
 
CREATE INDEX MMTTBLRCKYSTFLDDTRFKZKYTTBLR02 
       ON MM_TE_TABLRECKEYSTEFIELDDATARE ( 
           FK_ZKEYTETABLRECKE ) ;
 
CREATE TABLE MMCONTROLDEF4CPTSCHNGFRMCONTRO ( 
           FK_ZKEY_CONTROLDEF INTEGER            NOT NULL , 
           FK_ZKEY_CONTROLD02 INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMCNTRLDF4CPTSCHNGFRMCNTRDMMCN 
       ON MMCONTROLDEF4CPTSCHNGFRMCONTRO ( 
           FK_ZKEY_CONTROLDEF, 
           FK_ZKEY_CONTROLD02 ) ;
 
CREATE INDEX MMCNTRLDF4CPTSCHNGFRMCNTRFKZ01 
       ON MMCONTROLDEF4CPTSCHNGFRMCONTRO ( 
           FK_ZKEY_CONTROLDEF ) ;
 
CREATE INDEX MMCNTRLDF4CPTSCHNGFRMCNTRFKZ02 
       ON MMCONTROLDEF4CPTSCHNGFRMCONTRO ( 
           FK_ZKEY_CONTROLD02 ) ;
 
CREATE TABLE MMCONTROLDEF1CPTSPRNTCONTROLDE ( 
           FK_ZKEY_CONTROLDEF INTEGER            NOT NULL , 
           FK_ZKEY_CONTROLD02 INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMCNTRLDF1CPTSPRNTCNTRLDDMMCNT 
       ON MMCONTROLDEF1CPTSPRNTCONTROLDE ( 
           FK_ZKEY_CONTROLDEF, 
           FK_ZKEY_CONTROLD02 ) ;
 
CREATE INDEX MMCNTRLDF1CPTSPRNTCNTRLDFKZK01 
       ON MMCONTROLDEF1CPTSPRNTCONTROLDE ( 
           FK_ZKEY_CONTROLDEF ) ;
 
CREATE INDEX MMCNTRLDF1CPTSPRNTCNTRLDFKZK02 
       ON MMCONTROLDEF1CPTSPRNTCONTROLDE ( 
           FK_ZKEY_CONTROLD02 ) ;
 
CREATE TABLE MMCONTROLDEF2CPTSCHLDCONTROLDE ( 
           FK_ZKEY_CONTROLDEF INTEGER            NOT NULL , 
           FK_ZKEY_CONTROLD02 INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMCNTRLDF2CPTSCHLDCNTRLDDMMCNT 
       ON MMCONTROLDEF2CPTSCHLDCONTROLDE ( 
           FK_ZKEY_CONTROLDEF, 
           FK_ZKEY_CONTROLD02 ) ;
 
CREATE INDEX MMCNTRLDF2CPTSCHLDCNTRLDFKZK01 
       ON MMCONTROLDEF2CPTSCHLDCONTROLDE ( 
           FK_ZKEY_CONTROLDEF ) ;
 
CREATE INDEX MMCNTRLDF2CPTSCHLDCNTRLDFKZK02 
       ON MMCONTROLDEF2CPTSCHLDCONTROLDE ( 
           FK_ZKEY_CONTROLD02 ) ;
 
CREATE TABLE MM_SA_ENTITY_SNVLVDNSUBJECTARE ( 
           FK_ZKEY_SUBJECTARE INTEGER            NOT NULL , 
           FK_ZKEY_SA_ENTITY  INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMSNTTYSNVLVDNSBJCTRDMMSNTTYSN 
       ON MM_SA_ENTITY_SNVLVDNSUBJECTARE ( 
           FK_ZKEY_SUBJECTARE, 
           FK_ZKEY_SA_ENTITY ) ;
 
CREATE INDEX MMSNTTYSNVLVDNSBJCTRFKZKYSBJ01 
       ON MM_SA_ENTITY_SNVLVDNSUBJECTARE ( 
           FK_ZKEY_SUBJECTARE ) ;
 
CREATE INDEX MMSNTTYSNVLVDNSBJCTRFKZKYSNT02 
       ON MM_SA_ENTITY_SNVLVDNSUBJECTARE ( 
           FK_ZKEY_SA_ENTITY ) ;
 
CREATE TABLE MMTETABLRECDATARELMPLMNTSERENT ( 
           FK_ZKEY_ER_ENTITY  INTEGER            NOT NULL , 
           FKZKEYTETABLRECDAT INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMTTBLRCDTRLMPLMNTSRNTDMMTTBLR 
       ON MMTETABLRECDATARELMPLMNTSERENT ( 
           FK_ZKEY_ER_ENTITY, 
           FKZKEYTETABLRECDAT ) ;
 
CREATE INDEX MMTTBLRCDTRLMPLMNTSRNTFKZKYR01 
       ON MMTETABLRECDATARELMPLMNTSERENT ( 
           FK_ZKEY_ER_ENTITY ) ;
 
CREATE INDEX MMTTBLRCDTRLMPLMNTSRNTFKZKYT02 
       ON MMTETABLRECDATARELMPLMNTSERENT ( 
           FKZKEYTETABLRECDAT ) ;
 
CREATE TABLE MMTEPHYSICALDATATYPECNMPLMNTZD ( 
           FK_ZKEY_Z_DOMAIN   INTEGER            NOT NULL , 
           FKZKEYTEPHYSICALDA INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMTPHYSCLDTTYPCNMPLMNTZDDMMTPH 
       ON MMTEPHYSICALDATATYPECNMPLMNTZD ( 
           FK_ZKEY_Z_DOMAIN, 
           FKZKEYTEPHYSICALDA ) ;
 
CREATE INDEX MMTPHYSCLDTTYPCNMPLMNTZDFKZK01 
       ON MMTEPHYSICALDATATYPECNMPLMNTZD ( 
           FK_ZKEY_Z_DOMAIN ) ;
 
CREATE INDEX MMTPHYSCLDTTYPCNMPLMNTZDFKZK02 
       ON MMTEPHYSICALDATATYPECNMPLMNTZD ( 
           FKZKEYTEPHYSICALDA ) ;
 
CREATE TABLE MM_SA_RELTYPESNVLVDNSUBJECTARE ( 
           FK_ZKEY_SUBJECTARE INTEGER            NOT NULL , 
           FK_ZKEY_SA_RELTYPE INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMSRLTYPSNVLVDNSBJCTRDMMSRLTYP 
       ON MM_SA_RELTYPESNVLVDNSUBJECTARE ( 
           FK_ZKEY_SUBJECTARE, 
           FK_ZKEY_SA_RELTYPE ) ;
 
CREATE INDEX MMSRLTYPSNVLVDNSBJCTRFKZKYSB01 
       ON MM_SA_RELTYPESNVLVDNSUBJECTARE ( 
           FK_ZKEY_SUBJECTARE ) ;
 
CREATE INDEX MMSRLTYPSNVLVDNSBJCTRFKZKYSR02 
       ON MM_SA_RELTYPESNVLVDNSUBJECTARE ( 
           FK_ZKEY_SA_RELTYPE ) ;
 
CREATE TABLE MM_UIS_ENTITY_HSMNTLODATTRIBUT ( 
           FK_ZKEYLODATTRIBUT INTEGER            NOT NULL , 
           FK_ZKEY_UIS_ENTITY INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMSNTTYHSMNTLDTTRBTDMMSNTTYHSM 
       ON MM_UIS_ENTITY_HSMNTLODATTRIBUT ( 
           FK_ZKEYLODATTRIBUT, 
           FK_ZKEY_UIS_ENTITY ) ;
 
CREATE INDEX MMSNTTYHSMNTLDTTRBTFKZKYLDTT01 
       ON MM_UIS_ENTITY_HSMNTLODATTRIBUT ( 
           FK_ZKEYLODATTRIBUT ) ;
 
CREATE INDEX MMSNTTYHSMNTLDTTRBTFKZKYSNTT02 
       ON MM_UIS_ENTITY_HSMNTLODATTRIBUT ( 
           FK_ZKEY_UIS_ENTITY ) ;
 
CREATE TABLE MM_UIS_ENTITY_HSLSTLODATTRIBUT ( 
           FK_ZKEYLODATTRIBUT INTEGER            NOT NULL , 
           FK_ZKEY_UIS_ENTITY INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMSNTTYHSLSTLDTTRBTDMMSNTTYHSL 
       ON MM_UIS_ENTITY_HSLSTLODATTRIBUT ( 
           FK_ZKEYLODATTRIBUT, 
           FK_ZKEY_UIS_ENTITY ) ;
 
CREATE INDEX MMSNTTYHSLSTLDTTRBTFKZKYLDTT01 
       ON MM_UIS_ENTITY_HSLSTLODATTRIBUT ( 
           FK_ZKEYLODATTRIBUT ) ;
 
CREATE INDEX MMSNTTYHSLSTLDTTRBTFKZKYSNTT02 
       ON MM_UIS_ENTITY_HSLSTLODATTRIBUT ( 
           FK_ZKEY_UIS_ENTITY ) ;
 
CREATE TABLE MMTEPHYSICALDATATYPESVLBLFRTED ( 
           FK_ZKEYTEDBMSSOURC INTEGER            NOT NULL , 
           FKZKEYTEPHYSICALDA INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMTPHYSCLDTTYPSVLBLFRTDDMMTPHY 
       ON MMTEPHYSICALDATATYPESVLBLFRTED ( 
           FK_ZKEYTEDBMSSOURC, 
           FKZKEYTEPHYSICALDA ) ;
 
CREATE INDEX MMTPHYSCLDTTYPSVLBLFRTDFKZKY01 
       ON MMTEPHYSICALDATATYPESVLBLFRTED ( 
           FK_ZKEYTEDBMSSOURC ) ;
 
CREATE INDEX MMTPHYSCLDTTYPSVLBLFRTDFKZKY02 
       ON MMTEPHYSICALDATATYPESVLBLFRTED ( 
           FKZKEYTEPHYSICALDA ) ;
 
CREATE TABLE MM_Z_USER_BELONGTO_INSTALLATIO ( 
           FK_ZKEYINSTALLATIO INTEGER            NOT NULL , 
           FK_ZKEY_Z_USER     INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMZUSERBELONGTNSTLLTDMMZSRBLNG 
       ON MM_Z_USER_BELONGTO_INSTALLATIO ( 
           FK_ZKEYINSTALLATIO, 
           FK_ZKEY_Z_USER ) ;
 
CREATE INDEX MMZUSERBLNGTNSTLLTFKZKYNSTLL01 
       ON MM_Z_USER_BELONGTO_INSTALLATIO ( 
           FK_ZKEYINSTALLATIO ) ;
 
CREATE INDEX MMZUSERBELONGTONSTLLTFKZKYZS02 
       ON MM_Z_USER_BELONGTO_INSTALLATIO ( 
           FK_ZKEY_Z_USER ) ;
 
CREATE TABLE MM_REPOSITORYCLIENT_HAS_Z_USER ( 
           FK_ZKEY_Z_USER     INTEGER            NOT NULL , 
           FKZKEYREPOSITORYCL INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMREPOSITRYCLNTHSZSRDMMRPSTRYC 
       ON MM_REPOSITORYCLIENT_HAS_Z_USER ( 
           FK_ZKEY_Z_USER, 
           FKZKEYREPOSITORYCL ) ;
 
CREATE INDEX MMREPOSITORYCLNTHSZSRFKZKYZS01 
       ON MM_REPOSITORYCLIENT_HAS_Z_USER ( 
           FK_ZKEY_Z_USER ) ;
 
CREATE INDEX MMRPSTRYCLNTHSZSRFKZKYRPSTRY02 
       ON MM_REPOSITORYCLIENT_HAS_Z_USER ( 
           FKZKEYREPOSITORYCL ) ;
 
CREATE TABLE MM_CPLR_ISREUSEDBY_CPLR ( 
           FK_ZKEY_CPLR       INTEGER            NOT NULL , 
           FK_ZKEY_CPLR02     INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMCPLRISRESDBYCPLRDMMCPLRSRSDB 
       ON MM_CPLR_ISREUSEDBY_CPLR ( 
           FK_ZKEY_CPLR, 
           FK_ZKEY_CPLR02 ) ;
 
CREATE INDEX MMCPLRISREUSEDBYCPLRFKZKYCPL01 
       ON MM_CPLR_ISREUSEDBY_CPLR ( 
           FK_ZKEY_CPLR ) ;
 
CREATE INDEX MMCPLRISRESDBYCPLRFKZKYCPLR002 
       ON MM_CPLR_ISREUSEDBY_CPLR ( 
           FK_ZKEY_CPLR02 ) ;
 
CREATE TABLE MM_DIALOG_HAS_VIEWOBJREF ( 
           FK_ZKEY_VIEWOBJREF INTEGER            NOT NULL , 
           FK_ZKEY_DIALOG     INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMDIALOGHASVIEWOBJREFDMMDLGHSV 
       ON MM_DIALOG_HAS_VIEWOBJREF ( 
           FK_ZKEY_VIEWOBJREF, 
           FK_ZKEY_DIALOG ) ;
 
CREATE INDEX MMDIALOGHASVIWBJRFFKZKYVWBJR01 
       ON MM_DIALOG_HAS_VIEWOBJREF ( 
           FK_ZKEY_VIEWOBJREF ) ;
 
CREATE INDEX MMDIALOGHASVIEWOBJREFFKZKYDL02 
       ON MM_DIALOG_HAS_VIEWOBJREF ( 
           FK_ZKEY_DIALOG ) ;
 
CREATE TABLE MM_EXECCOMPOSITESGRPNGFZMETADE ( 
           FK_ZKEY_Z_METADEF  INTEGER            NOT NULL , 
           FKZKEYEXECCOMPOSIT INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMXCCMPSTSGRPNGFZMTDDMMXCCMPST 
       ON MM_EXECCOMPOSITESGRPNGFZMETADE ( 
           FK_ZKEY_Z_METADEF, 
           FKZKEYEXECCOMPOSIT ) ;
 
CREATE INDEX MMXCCMPSTSGRPNGFZMTDFKZKYZMT01 
       ON MM_EXECCOMPOSITESGRPNGFZMETADE ( 
           FK_ZKEY_Z_METADEF ) ;
 
CREATE INDEX MMXCCMPSTSGRPNGFZMTDFKZKYXCC02 
       ON MM_EXECCOMPOSITESGRPNGFZMETADE ( 
           FKZKEYEXECCOMPOSIT ) ;
 
CREATE TABLE MMDIALOGCNTNSPTNCPLREUSEABLEIT ( 
           FKZKEYCPLREUSEABLE INTEGER            NOT NULL , 
           FK_ZKEY_DIALOG     INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMDLGCNTNSPTNCPLRSBLTDMMDLGCNT 
       ON MMDIALOGCNTNSPTNCPLREUSEABLEIT ( 
           FKZKEYCPLREUSEABLE, 
           FK_ZKEY_DIALOG ) ;
 
CREATE INDEX MMDLGCNTNSPTNCPLRSBLTFKZKYCP01 
       ON MMDIALOGCNTNSPTNCPLREUSEABLEIT ( 
           FKZKEYCPLREUSEABLE ) ;
 
CREATE INDEX MMDLGCNTNSPTNCPLRSBLTFKZKYDL02 
       ON MMDIALOGCNTNSPTNCPLREUSEABLEIT ( 
           FK_ZKEY_DIALOG ) ;
 
CREATE TABLE MMDIALOGCNTNSWNDWCPLREUSEABLEI ( 
           FKZKEYCPLREUSEABLE INTEGER            NOT NULL , 
           FK_ZKEY_DIALOG     INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMDLGCNTNSWNDWCPLRSBLDMMDLGCNT 
       ON MMDIALOGCNTNSWNDWCPLREUSEABLEI ( 
           FKZKEYCPLREUSEABLE, 
           FK_ZKEY_DIALOG ) ;
 
CREATE INDEX MMDLGCNTNSWNDWCPLRSBLFKZKYCP01 
       ON MMDIALOGCNTNSWNDWCPLREUSEABLEI ( 
           FKZKEYCPLREUSEABLE ) ;
 
CREATE INDEX MMDLGCNTNSWNDWCPLRSBLFKZKYDL02 
       ON MMDIALOGCNTNSWNDWCPLREUSEABLEI ( 
           FK_ZKEY_DIALOG ) ;
 
CREATE TABLE MMDIALOGCNTNSGRPCPLREUSEABLEIT ( 
           FKZKEYCPLREUSEABLE INTEGER            NOT NULL , 
           FK_ZKEY_DIALOG     INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMDLGCNTNSGRPCPLRSBLTDMMDLGCNT 
       ON MMDIALOGCNTNSGRPCPLREUSEABLEIT ( 
           FKZKEYCPLREUSEABLE, 
           FK_ZKEY_DIALOG ) ;
 
CREATE INDEX MMDLGCNTNSGRPCPLRSBLTFKZKYCP01 
       ON MMDIALOGCNTNSGRPCPLREUSEABLEIT ( 
           FKZKEYCPLREUSEABLE ) ;
 
CREATE INDEX MMDLGCNTNSGRPCPLRSBLTFKZKYDL02 
       ON MMDIALOGCNTNSGRPCPLREUSEABLEIT ( 
           FK_ZKEY_DIALOG ) ;
 
CREATE TABLE MM_Z_ACTION_ACTIVATES_WINDOW ( 
           FK_ZKEY_WINDOW     INTEGER            NOT NULL , 
           FK_ZKEY_Z_ACTION   INTEGER            NOT NULL  ) ;
 
CREATE UNIQUE INDEX MMZACTIONACTIVTSWNDWDMMZCTNCTV 
       ON MM_Z_ACTION_ACTIVATES_WINDOW ( 
           FK_ZKEY_WINDOW, 
           FK_ZKEY_Z_ACTION ) ;
 
CREATE INDEX MMZACTIONACTIVTSWNDWFKZKYWND01 
       ON MM_Z_ACTION_ACTIVATES_WINDOW ( 
           FK_ZKEY_WINDOW ) ;
 
CREATE INDEX MMZACTIONACTIVTSWNDWFKZKYZCT02 
       ON MM_Z_ACTION_ACTIVATES_WINDOW ( 
           FK_ZKEY_Z_ACTION ) ;
 
 
