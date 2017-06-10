#include "constants.h"

Constants* Constants::m_pinstance = 0;

Constants::Constants()
{

}

Constants::~Constants()
{
    if (m_pinstance != 0)
        delete m_pinstance;
}

Constants& Constants::getInstance()
{
    if (m_pinstance == 0)
         m_pinstance = new Constants();

    return *m_pinstance;
}
