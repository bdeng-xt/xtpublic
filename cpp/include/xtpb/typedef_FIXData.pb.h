#pragma once
#include "FIXData.pb.h" 
#include "safe_ptr.h"

//////typedef for FIXData
namespace XT {
#if defined(USE_BOOST_SHARED_PTR)
#include <boost/smart_ptr.hpp>
typedef boost::shared_ptr<FieldMetrics> FieldMetricsPtr;
typedef boost::shared_ptr<FieldBase> FieldBasePtr;

#elif defined(USE_STD_SHARED_PTR)

typedef sf::contfree_safe_ptr<FieldMetrics> FieldMetricsPtr;
typedef sf::contfree_safe_ptr<FieldBase> FieldBasePtr;

#elif defined(USE_SAFE_PTR)

typedef sf::safe_ptr<FieldMetrics> FieldMetricsPtr;
typedef sf::safe_ptr<FieldBase> FieldBasePtr;

#else
#include <memory>
typedef std::shared_ptr<FieldMetrics> FieldMetricsPtr;
typedef std::shared_ptr<FieldBase> FieldBasePtr;
#endif


typedef sf::safe_ptr<FieldMetrics> FieldMetricsSafePtr;
typedef sf::safe_ptr<FieldBase> FieldBaseSafePtr;

typedef sf::contfree_safe_ptr<FieldMetrics> FieldMetricsContFreePtr;
typedef sf::contfree_safe_ptr<FieldBase> FieldBaseContFreePtr;
}//namespace XT
//////end typedef for FIXData

