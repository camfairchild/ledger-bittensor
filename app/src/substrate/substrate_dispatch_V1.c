/*******************************************************************************
 *  (c) 2019 - 2022 Zondax AG
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#include "substrate_dispatch_V1.h"
#include "substrate_strings.h"
#include "zxmacros.h"
#include <stdint.h>
#ifdef LEDGER_SPECIFIC
#include "bolos_target.h"
#endif

__Z_INLINE parser_error_t _readMethod_balances_transfer_V1(
    parser_context_t* c, pd_balances_transfer_V1_t* m)
{
    CHECK_ERROR(_readLookupasStaticLookupSource_V1(c, &m->dest))
    CHECK_ERROR(_readCompactBalance(c, &m->amount))
    return parser_ok;
}

__Z_INLINE parser_error_t _readMethod_balances_transfer_keep_alive_V1(
    parser_context_t* c, pd_balances_transfer_keep_alive_V1_t* m)
{
    CHECK_ERROR(_readLookupasStaticLookupSource_V1(c, &m->dest))
    CHECK_ERROR(_readCompactBalance(c, &m->amount))
    return parser_ok;
}

__Z_INLINE parser_error_t _readMethod_balances_transfer_all_V1(
    parser_context_t* c, pd_balances_transfer_all_V1_t* m)
{
    CHECK_ERROR(_readLookupasStaticLookupSource_V1(c, &m->dest))
    CHECK_ERROR(_readbool(c, &m->keep_alive))
    return parser_ok;
}

__Z_INLINE parser_error_t _readMethod_subtensor_module_add_stake_V1(
    parser_context_t* c, pd_subtensor_module_add_stake_V1_t * m)
{
    CHECK_ERROR(_readStakingAddress32_V1(c, &m->hotkey))
    CHECK_ERROR(_readBalance(c, &m->amount_staked ))
    return parser_ok;
}

__Z_INLINE parser_error_t _readMethod_subtensor_module_remove_stake_V1(
    parser_context_t* c, pd_subtensor_module_remove_stake_V1_t * m)
{
    CHECK_ERROR(_readStakingAddress32_V1(c, &m->hotkey))
    CHECK_ERROR(_readBalance(c, &m->amount_unstaked ))
    return parser_ok;
}

#ifdef SUBSTRATE_PARSER_FULL
#ifndef TARGET_NANOS
#endif

#endif

parser_error_t _readMethod_V1(
    parser_context_t* c,
    uint8_t moduleIdx,
    uint8_t callIdx,
    pd_Method_V1_t* method)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {
    case 0x0500: /* module 5 call 0 */
        CHECK_ERROR(_readMethod_balances_transfer_V1(c, &method->nested.balances_transfer_V1))
        break;
    case 0x0503: /* module 5 call 3 */
        CHECK_ERROR(_readMethod_balances_transfer_keep_alive_V1(c, &method->nested.balances_transfer_keep_alive_V1))
        break;
    case 0x0504: /* module 5 call 4 */
        CHECK_ERROR(_readMethod_balances_transfer_all_V1(c, &method->basic.balances_transfer_all_V1))
        break;
    
    case 0x0802: /* module 8 call 2 */
        CHECK_ERROR(_readMethod_subtensor_module_add_stake_V1(c, &method->nested.subtensor_module_add_stake_V1))
        break;
    case 0x0803: /* module 8 call 3 */
        CHECK_ERROR(_readMethod_subtensor_module_remove_stake_V1(c, &method->nested.subtensor_module_remove_stake_V1))
        break;

#ifdef SUBSTRATE_PARSER_FULL
#ifndef TARGET_NANOS
#endif

#endif
    default:
        return parser_unexpected_callIndex;
    }

    return parser_ok;
}

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////

const char* _getMethod_ModuleName_V1(uint8_t moduleIdx)
{
    switch (moduleIdx) {
    case PD_CALL_BALANCES_V1:
        return STR_MO_BALANCES;
    case PD_CALL_SUBTENSOR_MODULE_V1:
        return STR_MO_SUBTENSOR_MODULE;
#ifdef SUBSTRATE_PARSER_FULL
#ifndef TARGET_NANOS
#endif

#endif
    default:
        return NULL;
    }

    return NULL;
}

const char* _getMethod_Name_V1(uint8_t moduleIdx, uint8_t callIdx)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {
    case 0x0500: /* module 5 call 0 */
        return STR_ME_TRANSFER;
    case 0x0503: /* module 5 call 3 */
        return STR_ME_TRANSFER_KEEP_ALIVE;
    case 0x0504: /* module 5 call 4 */
        return STR_ME_TRANSFER_ALL;

    case 0x0802: /* module 8 call 2 */
        return STR_ME_ADD_STAKE;
    case 0x0803: /* module 8 call 3 */
        return STR_ME_REMOVE_STAKE;
    
    default:
        return _getMethod_Name_V1_ParserFull(callPrivIdx);
    }

    return NULL;
}

const char* _getMethod_Name_V1_ParserFull(uint16_t callPrivIdx)
{
    switch (callPrivIdx) {
#ifdef SUBSTRATE_PARSER_FULL
#ifndef TARGET_NANOS
#endif

#endif
    default:
        return NULL;
    }

    return NULL;
}

uint8_t _getMethod_NumItems_V1(uint8_t moduleIdx, uint8_t callIdx)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {
    case 0x0500: /* module 5 call 0 */
        return 2;
    case 0x0503: /* module 5 call 3 */
        return 2;
    case 0x0504: /* module 5 call 4 */
        return 2;
    
    case 0x0802: /* module 8 call 2 */
        return 2;
    case 0x0803: /* module 8 call 3 */
        return 2;

#ifdef SUBSTRATE_PARSER_FULL
#ifndef TARGET_NANOS
#endif

#endif
    default:
        return 0;
    }

    return 0;
}

const char* _getMethod_ItemName_V1(uint8_t moduleIdx, uint8_t callIdx, uint8_t itemIdx)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {
    case 0x0500: /* module 5 call 0 */
        switch (itemIdx) {
        case 0:
            return STR_IT_dest;
        case 1:
            return STR_IT_amount;
        default:
            return NULL;
        }
    case 0x0503: /* module 5 call 3 */
        switch (itemIdx) {
        case 0:
            return STR_IT_dest;
        case 1:
            return STR_IT_amount;
        default:
            return NULL;
        }
    case 0x0504: /* module 5 call 4 */
        switch (itemIdx) {
        case 0:
            return STR_IT_dest;
        case 1:
            return STR_IT_keep_alive;
        default:
            return NULL;
        }

    case 0x0802: /* module 8 call 2 */
        switch (itemIdx) {
        case 0:
            return STR_IT_hotkey;
        case 1:
            return STR_IT_amount_staked;
        default:
            return NULL;
        }
    case 0x0803: /* module 8 call 3 */
        switch (itemIdx) {
        case 0:
            return STR_IT_hotkey;
        case 1:
            return STR_IT_amount_unstaked;
        default:
            return NULL;
        }
#ifdef SUBSTRATE_PARSER_FULL
#ifndef TARGET_NANOS
#endif

#endif
    default:
        return NULL;
    }

    return NULL;
}

parser_error_t _getMethod_ItemValue_V1(
    pd_Method_V1_t* m,
    uint8_t moduleIdx, uint8_t callIdx, uint8_t itemIdx,
    char* outValue, uint16_t outValueLen,
    uint8_t pageIdx, uint8_t* pageCount)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {
    case 0x0500: /* module 5 call 0 */
        switch (itemIdx) {
        case 0: /* balances_transfer_V1 - dest */;
            return _toStringLookupasStaticLookupSource_V1(
                &m->nested.balances_transfer_V1.dest,
                outValue, outValueLen,
                pageIdx, pageCount);
        case 1: /* balances_transfer_V1 - amount */;
            return _toStringCompactBalance(
                &m->nested.balances_transfer_V1.amount,
                outValue, outValueLen,
                pageIdx, pageCount);
        default:
            return parser_no_data;
        }
    case 0x0503: /* module 5 call 3 */
        switch (itemIdx) {
        case 0: /* balances_transfer_keep_alive_V1 - dest */;
            return _toStringLookupasStaticLookupSource_V1(
                &m->nested.balances_transfer_keep_alive_V1.dest,
                outValue, outValueLen,
                pageIdx, pageCount);
        case 1: /* balances_transfer_keep_alive_V1 - amount */;
            return _toStringCompactBalance(
                &m->nested.balances_transfer_keep_alive_V1.amount,
                outValue, outValueLen,
                pageIdx, pageCount);
        default:
            return parser_no_data;
        }
    case 0x0504: /* module 5 call 4 */
        switch (itemIdx) {
        case 0: /* balances_transfer_all_V1 - dest */;
            return _toStringLookupasStaticLookupSource_V1(
                &m->basic.balances_transfer_all_V1.dest,
                outValue, outValueLen,
                pageIdx, pageCount);
        case 1: /* balances_transfer_all_V1 - keep_alive */;
            return _toStringbool(
                &m->basic.balances_transfer_all_V1.keep_alive,
                outValue, outValueLen,
                pageIdx, pageCount);
        default:
            return parser_no_data;
        }
    
    case 0x0802: /* module 8 call 2 */
        switch (itemIdx) {
        case 0: /* subtensor_module_add_stake_V1 - hotkey */;
            return _toStringStakingAddress32_V1(
                &m->nested.subtensor_module_add_stake_V1.hotkey,
                outValue, outValueLen,
                pageIdx, pageCount);
        case 1: /* subtensor_module_add_stake_V1 - amount_staked */;
            return _toStringBalance(
                &m->nested.subtensor_module_add_stake_V1.amount_staked,
                outValue, outValueLen,
                pageIdx, pageCount);
        default:
            return parser_no_data;
        }
    case 0x0803: /* module 8 call 3 */
        switch (itemIdx) {
        case 0: /* subtensor_module_remove_stake_V1 - hotkey */;
            return _toStringStakingAddress32_V1(
                &m->nested.subtensor_module_remove_stake_V1.hotkey,
                outValue, outValueLen,
                pageIdx, pageCount);
        case 1: /* subtensor_module_remove_stake_V1 - amount_unstaked */;
            return _toStringBalance(
                &m->nested.subtensor_module_remove_stake_V1.amount_unstaked,
                outValue, outValueLen,
                pageIdx, pageCount);
        default:
            return parser_no_data;
        }

    
#ifdef SUBSTRATE_PARSER_FULL
#ifndef TARGET_NANOS
#endif

#endif
    default:
        return parser_ok;
    }

    return parser_ok;
}

bool _getMethod_ItemIsExpert_V1(uint8_t moduleIdx, uint8_t callIdx, uint8_t itemIdx)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {

    default:
        return false;
    }
}

bool _getMethod_IsNestingSupported_V1(uint8_t moduleIdx, uint8_t callIdx)
{
    uint16_t callPrivIdx = ((uint16_t)moduleIdx << 8u) + callIdx;

    switch (callPrivIdx) {
    case 0x0504: // Balances:Transfer all
        return false;
    default:
        return true;
    }
}
