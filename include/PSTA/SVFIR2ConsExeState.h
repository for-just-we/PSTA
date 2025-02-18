//
// Created by prophe cheng on 2025/1/17.
//

#ifndef PSTA_SVFIR2CONSEXESTATE_H
#define PSTA_SVFIR2CONSEXESTATE_H

#include "Bases/ConsExeState.h"
#include "SVFIR/SVFIR.h"

namespace SVF
{
class SVFIR2ConsExeState
{
public:
    typedef ExeState::Addrs Addrs;

    SVFIR2ConsExeState() = default;

    void setEs(ConsExeState *es)
    {
        _es = es;
    }

    ConsExeState *getEs()
    {
        return _es;
    }

    virtual ~SVFIR2ConsExeState();

    /// Translator for llvm ir
    //{%
    /// https://llvm.org/docs/LangRef.html#alloca-instruction
    void translateAddr(const AddrStmt *addr);

    /// https://llvm.org/docs/LangRef.html#binary-operations
    void translateBinary(const BinaryOPStmt *binary);

    /// https://llvm.org/docs/LangRef.html#icmp-instruction
    void translateCmp(const CmpStmt *cmp);

    /// https://llvm.org/docs/LangRef.html#load-instruction
    void translateLoad(const LoadStmt *load);

    /// https://llvm.org/docs/LangRef.html#store-instruction
    void translateStore(const StoreStmt *store);

    /// https://llvm.org/docs/LangRef.html#conversion-operations
    void translateCopy(const CopyStmt *copy);

    /// https://llvm.org/docs/LangRef.html#call-instruction
    void translateCall(const CallPE *callPE);

    void translateRet(const RetPE *retPE);

    /// https://llvm.org/docs/LangRef.html#getelementptr-instruction
    void translateGep(const GepStmt *gep, bool isGlobal);

    /// https://llvm.org/docs/LangRef.html#select-instruction
    void translateSelect(const SelectStmt *select);

    /// https://llvm.org/docs/LangRef.html#i-phi
    void translatePhi(const PhiStmt *phi);

    //%}
    //%}

    /// Return the expr of gep object given a base and offset
    Addrs getGepObjAddress(u32_t base, s32_t offset);

    /// Return the offset expression of a GepStmt
    std::pair<s32_t, s32_t> getGepOffset(const GepStmt *gep);

    /// Init ConZ3Expr for ObjVar
    void initObjVar(const ObjVar *objVar, u32_t varId);


    void initSVFVar(u32_t varId);

    void moveToGlobal();

    /// The physical address starts with 0x7f...... + idx
    static inline u32_t getVirtualMemAddress(u32_t idx)
    {
        return ExeState::getVirtualMemAddress(idx);
    }

    /// Check bit value of val start with 0x7F000000, filter by 0xFF000000
    static inline bool isVirtualMemAddress(u32_t val)
    {
        return ExeState::isVirtualMemAddress(val);
    }

    /// Return the internal index if idx is an address otherwise return the value of idx
    static inline u32_t getInternalID(u32_t idx)
    {
        return ExeState::getInternalID(idx);
    }

    inline bool inVarToValTable(u32_t id) const
    {
        return _es->inVarToValTable(id);
    }

    inline bool inVarToAddrsTable(u32_t id) const
    {
        return _es->inVarToAddrsTable(id);
    }

    inline bool inLocToValTable(u32_t id) const
    {
        return _es->inLocToValTable(id);
    }

    inline bool inLocToAddrsTable(u32_t id) const
    {
        return _es->inLocToAddrsTable(id);
    }

protected:
    ConsExeState *_es{nullptr};
}; // end class SVFIR2ConsExeState
} // end namespace SVF

#endif //PSTA_SVFIR2CONSEXESTATE_H
