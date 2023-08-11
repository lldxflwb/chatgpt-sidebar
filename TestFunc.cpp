//
// Created by 陈嘉乐 on 2023/8/7.
//

#include "TestFunc.h"

#include "utils/Proxy/ProxyConfigWidgetPublic.h"
#include "utils/Proxy/ProxyActionHttp.h"

#include <variant>

void TestFunc::TestProxyConfigWidgetPublic() {
    auto pconfig = std::make_shared<ProxyActionHttp::ProxyConfigHttp>("","6863","","");
    ProxyConfigWidgetPublic * p = new ProxyConfigWidgetPublic(pconfig);
    p->show();
}
