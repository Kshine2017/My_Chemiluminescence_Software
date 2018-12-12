#include "stndog.h"
#include <QDebug>

StnDog::StnDog()
{
    const char* scope =
            "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>"
            "<haspscope/>";

    unsigned char vendor_code[] =
            "VGGuMs7oICGjDsRAz2GWwWHhF2mSbPJxHTfWglbTI6aYyRrImkmlbfSOAqpuhD0YFv9npUwUe3O0fiKG"
            "hYPum1Y8hLsjahsx994ZhzI96+f77K+Irri5wk4hRsG+E0yr2pilPcTUbvFzr6756LpPQdBAftQaTPBh"
            "3ysLYEfKfff3wCqenXvEPhjnMX/0dH2/wFF5pEvBOy928eO+7kI6qoOw/W7dEvgCtrPJMZHqZqO4TLhI"
            "RcHf/6zs9xRF/cYX5MBpra9cz9UERGuoRdN3dcYlu+pJ+dpTpqcqSuAvSDXuh+oJ1ecRt32Zmow+cX3u"
            "xzHgA+uqTJmmoR4XG8drnacANHVqJy+D5yLugBv8WYKEoUaURbiREcCMSFbi2PTWPI/KqgtkhUz5Cqp2"
            "BQvBtbsk7EQOu4wifFbpmPXZoF39tKTheFwkP5jVdNXdVCTYiKe/ipMPdQG6cdUyJGLuUh5lmCEcPQzV"
            "NU7wscohvY/R1eDg5sH10ngXWhcVxF2yHZLaG8YPa8nIW6GhxCxQ3Net4YYmWqzG1roOLqK1FblHNNh8"
            "SS+sORpFNh7i/SPIOUhrR04/51155M0TZaGbAHiIQwTv77CZJZkp02tBElLeOHg0Awo4nZHVwPAr2Wa7"
            "28gI4CzRxsoRyr/fy75l1CdEdP7xztSALrY06984KPWYyWfoWUx2UNAdRse97B47ol/8YOAYut8R7DHe"
            "jL50OPXfK+Lis12w//Cu4HNtMR+3VnxEX8Epv76Is/9kwHqHOCgnqKj1NiXY+J36YjnxHVxFxb7BSYJo"
            "g2fgq4J3WOo8NrjrqULUZxs0TTJF2oaGwVJxXZQ1EQoXHLQI0dIhN53a0ssRApEyZjbaLGRsuaXsGQdq"
            "vbgsd3vu9wUryUl2wtkenUG2A8X9URSYgq5FFRildJg+Ul286aSm0yQJ/xr45Jm9mmJkkCIjUxptJhsf"
            "91vj8SrnDcMTGrsD2LGfPQ==";
    hasp_handle_t handle = HASP_INVALID_HANDLE_VALUE;
//    status = hasp_login_scope(0, scope, vendor_code, &handle);//20181213

    qDebug()<<"标志位："<<status;
}
