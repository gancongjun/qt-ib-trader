#ifndef contract_def
#define contract_def

#include <vector>
#include <string>

/*
    SAME_POS    = open/close leg value is same as combo
    OPEN_POS    = open
    CLOSE_POS   = close
    UNKNOWN_POS = unknown

*/
enum LegOpenClose { SAME_POS, OPEN_POS, CLOSE_POS, UNKNOWN_POS };

struct ComboLeg
{

   ComboLeg()
      :
      conId(0),
	  ratio(0),
	  openClose(0),
	  shortSaleSlot(0),
	  exemptCode(-1)
   {
   }

   long    conId;
   long    ratio;
   std::string action; //BUY/SELL/SSHORT

   std::string exchange;
   long    openClose; // LegOpenClose enum values

   // for stock legs when doing short sale
   long    shortSaleSlot; // 1 = clearing broker, 2 = third party
   std::string designatedLocation;
   int     exemptCode;

   bool operator==( const ComboLeg &other) const
   {
      return (conId == other.conId &&
         ratio == other.ratio &&
		 openClose == other.openClose &&
		 shortSaleSlot == other.shortSaleSlot &&
		 action.compare(other.action) == 0 &&
		 exchange.compare(other.exchange) == 0 &&
		 designatedLocation.compare(other.designatedLocation) == 0 &&
		 exemptCode == other.exemptCode);
   }
};

struct UnderComp
{
	UnderComp()
		: conId(0)
		, delta(0)
		, price(0)
	{}

	long	conId;
	double	delta;
	double	price;
};

struct Contract
{
   Contract()
      : conId(0)
	  , strike(0)
	  , includeExpired(false)
	  , comboLegs(NULL)
	  , underComp(NULL)
   {
   }

   long    conId;
   std::string symbol;
   std::string secType;
   std::string expiry;
   double  strike;
   std::string right;
   std::string multiplier;
   std::string exchange;
   std::string primaryExchange; // pick an actual (ie non-aggregate) exchange that the contract trades on.  DO NOT SET TO SMART.
   std::string currency;
   std::string localSymbol;
   bool includeExpired;
   std::string secIdType;		// CUSIP;SEDOL;ISIN;RIC
   std::string secId;

   // COMBOS
   std::string comboLegsDescrip; // received in open order 14 and up for all combos

   typedef std::vector<ComboLeg*> ComboLegList;
   ComboLegList* comboLegs;

   // delta neutral
   UnderComp* underComp;

public:

	// Helpers
	static void CloneComboLegs(ComboLegList& dst, const ComboLegList& src);
    static void CleanupComboLegs(ComboLegList&);
};

struct ContractDetails
{
   ContractDetails()
      : minTick(0)
	  , priceMagnifier(0)
	  , underConId(0)
	  , callable(false)
	  , putable(false)
	  , coupon(0)
	  , convertible(false)
	  , nextOptionPartial(false)
		
   {
   }

   Contract	summary;
   std::string	marketName;
   std::string	tradingClass;
   double	minTick;
   std::string	orderTypes;
   std::string	validExchanges;
   long		priceMagnifier;
   int		underConId;
   std::string	longName;
   std::string	contractMonth;
   std::string	industry;
   std::string	category;
   std::string	subcategory;
   std::string	timeZoneId;
   std::string	tradingHours;
   std::string	liquidHours;

   // BOND values
   std::string cusip;
   std::string ratings;
   std::string descAppend;
   std::string bondType;
   std::string couponType;
   bool callable;
   bool putable;
   double coupon;
   bool convertible;
   std::string maturity;
   std::string issueDate;
   std::string nextOptionDate;
   std::string nextOptionType;
   bool nextOptionPartial;
   std::string notes;
};

inline void
Contract::CloneComboLegs(ComboLegList& dst, const ComboLegList& src)
{
	CleanupComboLegs(dst);

	if (src.empty())
		return;

	dst.reserve(src.size());

	ComboLegList::const_iterator iter = src.begin();
	const ComboLegList::const_iterator iterEnd = src.end();

	for (; iter != iterEnd; ++iter) {
		const ComboLeg* leg = *iter;
		if (!leg)
			continue;
		dst.push_back(new ComboLeg(*leg));
	}
}

inline void
Contract::CleanupComboLegs(ComboLegList& legs)
{
	if (legs.empty())
		return;

	ComboLegList::iterator iter = legs.begin();
	const ComboLegList::iterator iterEnd = legs.end();

	for (; iter != iterEnd; ++iter) {
		delete *iter;
	}

	legs.clear();
}

#endif
