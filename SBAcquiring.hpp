/*++

Program name:

  Apostol Web Service

Module Name:

  SBAcquiring.hpp

Notices:

  Module: Sberbank Acquiring

Author:

  Copyright (c) Prepodobny Alen

  mailto: alienufo@inbox.ru
  mailto: ufocomp@gmail.com

--*/

#ifndef APOSTOL_ACQUIRING_HPP
#define APOSTOL_ACQUIRING_HPP
//----------------------------------------------------------------------------------------------------------------------

extern "C++" {

namespace Apostol {

    namespace Workers {

        //--------------------------------------------------------------------------------------------------------------

        //-- CSBAcquiring ----------------------------------------------------------------------------------------------

        //--------------------------------------------------------------------------------------------------------------

        class CSBAcquiring: public CApostolModule {
        private:

            CDateTime m_HeartbeatInterval;

            CHTTPProxyManager m_ProxyManager;

            CDateTime m_FixedDate;
            CDateTime m_CheckDate;

            CString m_ClientToken;

            TPairs<CStringList> m_Profile;

            void InitMethods() override;

            void SetObjectData(CHTTPServerConnection *AConnection, const CString &Token, const CJSON &Payload,
                const CString &Agent);

            static bool CheckAuthorizationData(CRequest *ARequest, CAuthorization &Authorization);

            void VerifyToken(const CString &Token);

            CHTTPProxy *GetProxy(CHTTPServerConnection *AConnection);

        protected:

            void DoProxy(CHTTPServerConnection *AConnection);

            void DoVerbose(CSocketEvent *Sender, CTCPConnection *AConnection, LPCTSTR AFormat, va_list args);
            bool DoProxyExecute(CTCPConnection *AConnection);
            void DoProxyException(CTCPConnection *AConnection, Delphi::Exception::Exception *AException);
            void DoEventHandlerException(CPollEventHandler *AHandler, Delphi::Exception::Exception *AException);

            void DoProxyConnected(CObject *Sender);
            void DoProxyDisconnected(CObject *Sender);

        public:

            explicit CSBAcquiring(CModuleProcess *AProcess);

            ~CSBAcquiring() override = default;

            static class CSBAcquiring *CreateModule(CModuleProcess *AProcess) {
                return new CSBAcquiring(AProcess);
            }

            bool CheckAuthorization(CHTTPServerConnection *AConnection, CAuthorization &Authorization);

            void Initialization(CModuleProcess *AProcess) override;

            void Heartbeat() override;

            bool Enabled() override;
            bool CheckConnection(CHTTPServerConnection *AConnection) override;

        };
    }
}

using namespace Apostol::Workers;
}
#endif //APOSTOL_ACQUIRING_HPP
