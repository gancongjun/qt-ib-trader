#ifndef execution_def
#define execution_def

#include <string>

struct Execution
{
   Execution()
   {
      shares = 0;
      price = 0;
      permId = 0;
      clientId = 0;
      orderId = 0;
	  cumQty = 0;
	  avgPrice = 0;
   }

   // main order fields
   std::string     execId;
   std::string     time;
   std::string     acctNumber;
   std::string     exchange;
   std::string     side;
   int         shares;
   double      price;
   int         permId;
   long        clientId;
   long        orderId;
   int         liquidation;
   int         cumQty;
   double      avgPrice;
};

struct ExecutionFilter
{
	ExecutionFilter()
		: m_clientId(0)
	{
	}

   // Filter fields
   long        m_clientId;
   std::string     m_acctCode;
   std::string     m_time;
   std::string     m_symbol;
   std::string     m_secType;
   std::string     m_exchange;
   std::string     m_side;
};

#endif // execution_def
