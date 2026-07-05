@echo off
setlocal

:: ============================================================
::  COMPRESSOR - Script de inicializacao
:: ============================================================

:: Adiciona MinGW ao PATH desta sessao
set "PATH=C:\msys64\ucrt64\bin;%PATH%"

:: Diretorio raiz do projeto (onde este .bat esta)
set "ROOT=%~dp0"
set "BACKEND=%ROOT%backend"
set "FRONTEND=%ROOT%frontend"
set "EXE=%BACKEND%\build\servidor.exe"

cls
echo.
echo  ==========================================
echo    COMPRESSOR - Iniciando aplicacao
echo  ==========================================
echo.

:: ----------------------------------------------------------
:: [1/3] Verificar / compilar backend
:: ----------------------------------------------------------
echo  [1/3] Verificando backend C++...

if not exist "%EXE%" (
    echo         servidor.exe nao encontrado. Compilando agora...
    echo.
    cd /d "%BACKEND%"
    cmake -G "MinGW Makefiles" -B build -S . >nul 2>&1
    if errorlevel 1 (
        echo  [ERRO] Falha ao configurar o CMake.
        echo         Verifique se o MinGW esta instalado em C:\msys64\ucrt64\bin
        pause
        exit /b 1
    )
    cmake --build build
    if errorlevel 1 (
        echo  [ERRO] Falha ao compilar o backend.
        pause
        exit /b 1
    )
    echo.
    echo         Compilacao concluida com sucesso!
    cd /d "%ROOT%"
) else (
    echo         servidor.exe encontrado. Pulando compilacao.
)

echo.

:: ----------------------------------------------------------
:: [2/3] Iniciar backend
:: ----------------------------------------------------------
echo  [2/3] Iniciando backend C++...
start "Backend - COMPRESSOR" cmd /k "title Backend - COMPRESSOR && echo Servidor rodando em http://localhost:8080 && echo. && "%EXE%""

:: Aguarda o backend subir antes de abrir o frontend
timeout /t 2 /nobreak >nul

:: ----------------------------------------------------------
:: [3/3] Iniciar frontend
:: ----------------------------------------------------------
echo  [3/3] Iniciando frontend React...
start "Frontend - COMPRESSOR" cmd /k "title Frontend - COMPRESSOR && echo Frontend rodando em http://localhost:5173 && echo. && cd /d "%FRONTEND%" && npm run dev"

:: Aguarda o Vite subir antes de abrir o navegador
echo.
echo  Aguardando servicos iniciarem...
timeout /t 4 /nobreak >nul

:: ----------------------------------------------------------
:: Abrir navegador
:: ----------------------------------------------------------
echo  Abrindo navegador em http://localhost:5173...
start "" http://localhost:5173

echo.
echo  ==========================================
echo    APLICACAO INICIADA!
echo    Backend:  http://localhost:8080
echo    Frontend: http://localhost:5173
echo  ==========================================
echo.
echo  Feche as janelas do backend e frontend
echo  para encerrar a aplicacao.
echo.
pause >nul
endlocal