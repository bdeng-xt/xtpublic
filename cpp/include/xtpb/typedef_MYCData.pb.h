#pragma once
#include "MYCData.pb.h" 
#include "safe_ptr.h"

//////typedef for MYCData
namespace MYC {
#if defined(USE_BOOST_SHARED_PTR)
#include <boost/smart_ptr.hpp>
typedef boost::shared_ptr<MYC_OrderError> MYC_OrderErrorPtr;
typedef boost::shared_ptr<MYC_SmartExecutionError> MYC_SmartExecutionErrorPtr;
typedef boost::shared_ptr<MYC_Direction> MYC_DirectionPtr;
typedef boost::shared_ptr<MYC_OpenClose> MYC_OpenClosePtr;
typedef boost::shared_ptr<MYC_InvestorTypes> MYC_InvestorTypesPtr;
typedef boost::shared_ptr<MYC_OrderType> MYC_OrderTypePtr;
typedef boost::shared_ptr<MYC_OrderStatus> MYC_OrderStatusPtr;
typedef boost::shared_ptr<MYC_TIF> MYC_TIFPtr;
typedef boost::shared_ptr<MYC_Currency> MYC_CurrencyPtr;
typedef boost::shared_ptr<MYC_Exchange> MYC_ExchangePtr;
typedef boost::shared_ptr<MYC_FeedType> MYC_FeedTypePtr;
typedef boost::shared_ptr<MYC_contract> MYC_contractPtr;
typedef boost::shared_ptr<MYC_account> MYC_accountPtr;
typedef boost::shared_ptr<MYC_config> MYC_configPtr;
typedef boost::shared_ptr<MYC_future_quote> MYC_future_quotePtr;
typedef boost::shared_ptr<MYC_stock_quote> MYC_stock_quotePtr;
typedef boost::shared_ptr<MYC_response> MYC_responsePtr;

#elif defined(USE_STD_SHARED_PTR)

typedef sf::contfree_safe_ptr<MYC_OrderError> MYC_OrderErrorPtr;
typedef sf::contfree_safe_ptr<MYC_SmartExecutionError> MYC_SmartExecutionErrorPtr;
typedef sf::contfree_safe_ptr<MYC_Direction> MYC_DirectionPtr;
typedef sf::contfree_safe_ptr<MYC_OpenClose> MYC_OpenClosePtr;
typedef sf::contfree_safe_ptr<MYC_InvestorTypes> MYC_InvestorTypesPtr;
typedef sf::contfree_safe_ptr<MYC_OrderType> MYC_OrderTypePtr;
typedef sf::contfree_safe_ptr<MYC_OrderStatus> MYC_OrderStatusPtr;
typedef sf::contfree_safe_ptr<MYC_TIF> MYC_TIFPtr;
typedef sf::contfree_safe_ptr<MYC_Currency> MYC_CurrencyPtr;
typedef sf::contfree_safe_ptr<MYC_Exchange> MYC_ExchangePtr;
typedef sf::contfree_safe_ptr<MYC_FeedType> MYC_FeedTypePtr;
typedef sf::contfree_safe_ptr<MYC_contract> MYC_contractPtr;
typedef sf::contfree_safe_ptr<MYC_account> MYC_accountPtr;
typedef sf::contfree_safe_ptr<MYC_config> MYC_configPtr;
typedef sf::contfree_safe_ptr<MYC_future_quote> MYC_future_quotePtr;
typedef sf::contfree_safe_ptr<MYC_stock_quote> MYC_stock_quotePtr;
typedef sf::contfree_safe_ptr<MYC_response> MYC_responsePtr;

#elif defined(USE_SAFE_PTR)

typedef sf::safe_ptr<MYC_OrderError> MYC_OrderErrorPtr;
typedef sf::safe_ptr<MYC_SmartExecutionError> MYC_SmartExecutionErrorPtr;
typedef sf::safe_ptr<MYC_Direction> MYC_DirectionPtr;
typedef sf::safe_ptr<MYC_OpenClose> MYC_OpenClosePtr;
typedef sf::safe_ptr<MYC_InvestorTypes> MYC_InvestorTypesPtr;
typedef sf::safe_ptr<MYC_OrderType> MYC_OrderTypePtr;
typedef sf::safe_ptr<MYC_OrderStatus> MYC_OrderStatusPtr;
typedef sf::safe_ptr<MYC_TIF> MYC_TIFPtr;
typedef sf::safe_ptr<MYC_Currency> MYC_CurrencyPtr;
typedef sf::safe_ptr<MYC_Exchange> MYC_ExchangePtr;
typedef sf::safe_ptr<MYC_FeedType> MYC_FeedTypePtr;
typedef sf::safe_ptr<MYC_contract> MYC_contractPtr;
typedef sf::safe_ptr<MYC_account> MYC_accountPtr;
typedef sf::safe_ptr<MYC_config> MYC_configPtr;
typedef sf::safe_ptr<MYC_future_quote> MYC_future_quotePtr;
typedef sf::safe_ptr<MYC_stock_quote> MYC_stock_quotePtr;
typedef sf::safe_ptr<MYC_response> MYC_responsePtr;

#else
#include <memory>
typedef std::shared_ptr<MYC_OrderError> MYC_OrderErrorPtr;
typedef std::shared_ptr<MYC_SmartExecutionError> MYC_SmartExecutionErrorPtr;
typedef std::shared_ptr<MYC_Direction> MYC_DirectionPtr;
typedef std::shared_ptr<MYC_OpenClose> MYC_OpenClosePtr;
typedef std::shared_ptr<MYC_InvestorTypes> MYC_InvestorTypesPtr;
typedef std::shared_ptr<MYC_OrderType> MYC_OrderTypePtr;
typedef std::shared_ptr<MYC_OrderStatus> MYC_OrderStatusPtr;
typedef std::shared_ptr<MYC_TIF> MYC_TIFPtr;
typedef std::shared_ptr<MYC_Currency> MYC_CurrencyPtr;
typedef std::shared_ptr<MYC_Exchange> MYC_ExchangePtr;
typedef std::shared_ptr<MYC_FeedType> MYC_FeedTypePtr;
typedef std::shared_ptr<MYC_contract> MYC_contractPtr;
typedef std::shared_ptr<MYC_account> MYC_accountPtr;
typedef std::shared_ptr<MYC_config> MYC_configPtr;
typedef std::shared_ptr<MYC_future_quote> MYC_future_quotePtr;
typedef std::shared_ptr<MYC_stock_quote> MYC_stock_quotePtr;
typedef std::shared_ptr<MYC_response> MYC_responsePtr;
#endif


typedef sf::safe_ptr<MYC_OrderError> MYC_OrderErrorSafePtr;
typedef sf::safe_ptr<MYC_SmartExecutionError> MYC_SmartExecutionErrorSafePtr;
typedef sf::safe_ptr<MYC_Direction> MYC_DirectionSafePtr;
typedef sf::safe_ptr<MYC_OpenClose> MYC_OpenCloseSafePtr;
typedef sf::safe_ptr<MYC_InvestorTypes> MYC_InvestorTypesSafePtr;
typedef sf::safe_ptr<MYC_OrderType> MYC_OrderTypeSafePtr;
typedef sf::safe_ptr<MYC_OrderStatus> MYC_OrderStatusSafePtr;
typedef sf::safe_ptr<MYC_TIF> MYC_TIFSafePtr;
typedef sf::safe_ptr<MYC_Currency> MYC_CurrencySafePtr;
typedef sf::safe_ptr<MYC_Exchange> MYC_ExchangeSafePtr;
typedef sf::safe_ptr<MYC_FeedType> MYC_FeedTypeSafePtr;
typedef sf::safe_ptr<MYC_contract> MYC_contractSafePtr;
typedef sf::safe_ptr<MYC_account> MYC_accountSafePtr;
typedef sf::safe_ptr<MYC_config> MYC_configSafePtr;
typedef sf::safe_ptr<MYC_future_quote> MYC_future_quoteSafePtr;
typedef sf::safe_ptr<MYC_stock_quote> MYC_stock_quoteSafePtr;
typedef sf::safe_ptr<MYC_response> MYC_responseSafePtr;

typedef sf::contfree_safe_ptr<MYC_OrderError> MYC_OrderErrorContFreePtr;
typedef sf::contfree_safe_ptr<MYC_SmartExecutionError> MYC_SmartExecutionErrorContFreePtr;
typedef sf::contfree_safe_ptr<MYC_Direction> MYC_DirectionContFreePtr;
typedef sf::contfree_safe_ptr<MYC_OpenClose> MYC_OpenCloseContFreePtr;
typedef sf::contfree_safe_ptr<MYC_InvestorTypes> MYC_InvestorTypesContFreePtr;
typedef sf::contfree_safe_ptr<MYC_OrderType> MYC_OrderTypeContFreePtr;
typedef sf::contfree_safe_ptr<MYC_OrderStatus> MYC_OrderStatusContFreePtr;
typedef sf::contfree_safe_ptr<MYC_TIF> MYC_TIFContFreePtr;
typedef sf::contfree_safe_ptr<MYC_Currency> MYC_CurrencyContFreePtr;
typedef sf::contfree_safe_ptr<MYC_Exchange> MYC_ExchangeContFreePtr;
typedef sf::contfree_safe_ptr<MYC_FeedType> MYC_FeedTypeContFreePtr;
typedef sf::contfree_safe_ptr<MYC_contract> MYC_contractContFreePtr;
typedef sf::contfree_safe_ptr<MYC_account> MYC_accountContFreePtr;
typedef sf::contfree_safe_ptr<MYC_config> MYC_configContFreePtr;
typedef sf::contfree_safe_ptr<MYC_future_quote> MYC_future_quoteContFreePtr;
typedef sf::contfree_safe_ptr<MYC_stock_quote> MYC_stock_quoteContFreePtr;
typedef sf::contfree_safe_ptr<MYC_response> MYC_responseContFreePtr;
}//namespace MYC
//////end typedef for MYCData

