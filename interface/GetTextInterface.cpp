//
// Created by 48449 on 2023/4/21.
//

#include "GetTextInterface.h"


GetTextInterface::GetTextInterface() :GetTextInterface(UseMode::DefaultMode,""){
}

GetTextInterface::GetTextInterface(GetTextInterface::UseMode mode, const QString &text) : mode(mode), text(text) {

}
