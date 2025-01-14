/*
 * Copyright (c) 2014, 2016, Oracle and/or its affiliates.
 * All rights reserved. Use is subject to license terms.
 *
 * This file is available and licensed under the following license:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the distribution.
 *  - Neither the name of Oracle Corporation nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include "Platform.h"

#ifdef POSIX

#ifndef POSIXPLATFORM_H
#define POSIXPLATFORM_H


class PosixPlatform : virtual public Platform{
public:
    PosixPlatform(void);
    virtual ~PosixPlatform(void);

public:
    virtual MessageResponse ShowResponseMessage(TString title, TString description);
    //virtual MessageResponse ShowResponseMessageB(TString description);

    virtual void SetCurrentDirectory(TString Value);

    virtual Module LoadLibrary(TString FileName);
    virtual void FreeLibrary(Module AModule);
    virtual Procedure GetProcAddress(Module AModule, std::string MethodName);
    virtual std::vector<TString> GetLibraryImports(const TString FileName);
    virtual std::vector<TString> FilterOutRuntimeDependenciesForPlatform(std::vector<TString> Imports);

    virtual Process* CreateProcess();
};


class PosixProcess : public Process {
private:
    pid_t FChildPID;
    sigset_t saveblock;
    int FOutputHandle;
    int FInputHandle;
#ifdef MAC
    struct sigaction savintr, savequit;
#endif //MAC
    bool FRunning;

    void Cleanup();
    bool ReadOutput();
    //static void ProcessOutput(Process *Instance, std::vector<TString> Output);

public:
    PosixProcess();
    virtual ~PosixProcess();

    virtual bool IsRunning();
    virtual bool Terminate();
    virtual bool Execute(const TString Application, const std::vector<TString> Arguments,
        bool AWait = false);
    virtual bool Wait();
    virtual TProcessID GetProcessID();
    virtual void SetInput(TString Value);
    virtual std::list<TString> GetOutput();
};

#endif //POSIXPLATFORM_H
#endif //POSX
