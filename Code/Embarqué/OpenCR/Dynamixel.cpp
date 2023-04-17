#include "Dynamixel.h"

Dynamixel2Arduino* connectDXL()
{
    Dynamixel2Arduino dxl(DXL_SERIAL, DXL_DIR_PIN);
    dxl.begin(DXL_BAUD_RATE);
    dxl.setPortProtocolVersion(DXL_PROTOCOL_VERSION);
    return &dxl;
}
