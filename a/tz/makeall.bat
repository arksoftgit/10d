IF "%1" == "x" goto :delobj
goto :start
:delobj
del ..\..\w\tz\*.obj /s
shift
:start
del *.err
del *.ler
cls
cd tzvmlip
nmake %1 -f tzvmlip.mak
cd ..\account
nmake %1 -f account.mak
cd ..\kzrpsrco
nmake %1 -f kzrpsrco.mak
rem cd ..\kzsirrep
rem nmake %1 -f kzsirrep.mak
cd ..\tzadcdod
nmake %1 -f tzadcdod.mak
cd ..\tzadwdod
nmake %1 -f tzadwdod.mak
cd ..\tzadwebd
nmake %1 -f tzadwebd.mak
cd ..\tzadwexp
nmake %1 -f tzadwexp.mak
cd ..\tzapdmaa
nmake %1 -f tzapdmaa.mak
cd ..\tzaxcfgd
nmake %1 -f tzaxcfgd.mak
cd ..\tzbmupdd
nmake %1 -f tzbmupdd.mak
cd ..\tzbrau2o
nmake %1 -f tzbrau2o.mak
cd ..\tzbraudo
nmake %1 -f tzbraudo.mak
cd ..\tzbrentd
nmake %1 -f tzbrentd.mak
cd ..\tzcmcpld
nmake %1 -f tzcmcpld.mak
cd ..\tzcmlpld
nmake %1 -f tzcmlpld.mak
cd ..\tzcmlpmd
nmake %1 -f tzcmlpmd.mak
cd ..\tzcmqcpo
nmake %1 -f tzcmqcpo.mak
cd ..\tzcmrevd
nmake %1 -f tzcmrevd.mak
cd ..\tzcmrptd
nmake %1 -f tzcmrptd.mak
cd ..\tzcmslpd
nmake %1 -f tzcmslpd.mak
cd ..\tzdbhtsd
nmake %1 -f tzdbhtsd.mak
cd ..\tzdmupdd
nmake %1 -f tzdmupdd.mak
cd ..\tzedcmpd
nmake %1 -f tzedcmpd.mak
cd ..\tzedfrmd
nmake %1 -f tzedfrmd.mak
cd ..\tzedvmld
nmake %1 -f tzedvmld.mak
cd ..\tzeremdd
nmake %1 -f tzeremdd.mak
cd ..\tzerrord
nmake %1 -f tzerrord.mak
cd ..\tzhkeyad
nmake %1 -f tzhkeyad.mak
cd ..\tzlodopr
nmake %1 -f tzlodopr.mak
cd ..\tzobrwad
nmake %1 -f tzobrwad.mak
cd ..\tzophdrd
nmake %1 -f tzophdrd.mak
cd ..\tzoprusd
nmake %1 -f tzoprusd.mak
cd ..\tzopsigd
nmake %1 -f tzopsigd.mak
cd ..\tzopupdd
nmake %1 -f tzopupdd.mak
cd ..\tzpeupdd
nmake %1 -f tzpeupdd.mak
cd ..\tzpnctad
nmake %1 -f tzpnctad.mak
cd ..\tzpnctld
nmake %1 -f tzpnctld.mak
cd ..\tzpncwdd
nmake %1 -f tzpncwdd.mak
cd ..\tzpnolad
nmake %1 -f tzpnolad.mak
cd ..\tzpntbad
nmake %1 -f tzpntbad.mak
cd ..\tzpntrad
nmake %1 -f tzpntrad.mak
cd ..\tzpnupgd
nmake %1 -f tzpnupgd.mak
cd ..\tzrepoad
nmake %1 -f tzrepoad.mak
cd ..\tzrpupdd
nmake %1 -f tzrpupdd.mak
cd ..\tzsiimpd
nmake %1 -f tzsiimpd.mak
cd ..\tztedbld
nmake %1 -f tztedbld.mak
cd ..\tzteupdd
nmake %1 -f tzteupdd.mak
cd ..\tzvmlopr
nmake %1 -f tzvmlopr.mak
cd ..\tzvmpopr
nmake %1 -f tzvmpopr.mak
cd ..\tzvsdbad
nmake %1 -f tzvsdbad.mak
cd ..\tzvsxcad
nmake %1 -f tzvsxcad.mak
cd ..\tzwdgrwd
nmake %1 -f tzwdgrwd.mak
cd ..\tzwdvord
nmake %1 -f tzwdvord.mak
cd ..\tzweb
nmake %1 -f tzweb.mak
rem cd ..\tzwebd
rem nmake %1 -f tzwebd.mak
rem cd ..\tzwebk
rem nmake %1 -f tzwebk.mak
rem cd ..\tzxsltdd
rem nmake %1 -f tzxsltdd.mak
cd ..\tzzmaind
nmake %1 -f tzzmaind.mak
cd ..\tzzolodd
nmake %1 -f tzzolodd.mak
cd ..\tzzolodq
nmake %1 -f tzzolodq.mak
rem cd ..\waccount
rem nmake %1 -f waccount.mak
cd ..
@call cds a ms
@cd kzmsgqaa
nmake -f kzmsgqaa.mak
@cd ..
qff *.err /q /12
@call cds a tz
cd tzlodopr
nmake %1 -f tzlodopr.mak
cd ..\kzrpsrco
nmake %1 -f kzrpsrco.mak
@cd..
qff *.err /q /11
qff *.err /q /12
qff *.err /q /91
qff *.ler /q /180
@call cds a ms
@dir *.err /s
@call cds a tz
@dir *.err
@echo Expected error sizes:
@echo                                    102 account.err
@echo                                  1,922 kzrpsrco.err
@echo                                    795 kzxmlpg2.err
@echo                                    133 tzcmlpldv.err
@echo                                    236 tzcmlpmo.err
@echo                                    363 tzcmrevd.err
@echo                                    125 tzpncwdd.err
@echo                                  1,465 tzrpsrco.err
@echo                                    170 tzvmplaa.err
@echo                                    129 tzwdlg6o.err
@echo                                    238 tzwebgl1.err
@echo               11 File(s)          5,687 bytes

dir *.ler