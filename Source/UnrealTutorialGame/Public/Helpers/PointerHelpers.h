#pragma once

#define SafePtrOr(TYPE, NAME, VAL, RET) TYPE* NAME = VAL; if (!NAME) return RET
#define EnsuredPtrOr(TYPE, NAME, VAL, RET) TYPE* NAME = VAL; if (!ensure(NAME)) return RET
#define SafePtr(TYPE, NAME, VAL) TYPE* NAME = VAL; if (!NAME) return
#define EnsuredPtr(TYPE, NAME, VAL) TYPE* NAME = VAL; if (!ensure(NAME)) return