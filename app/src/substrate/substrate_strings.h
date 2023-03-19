/*******************************************************************************
 *  (c) 2019 - 2023 Zondax AG
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
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

// Modules names
static const char* STR_MO_BALANCES = "Balances";

static const char* STR_MO_SUBTENSOR_MODULE = "SubtensorModule";

// Methods names

// === Balances ===
static const char* STR_ME_TRANSFER = "Transfer";
static const char* STR_ME_TRANSFER_KEEP_ALIVE = "Transfer keep alive";
static const char* STR_ME_TRANSFER_ALL = "Transfer all";

// === Subtensor Module ===
static const char* STR_ME_ADD_STAKE = "Add stake";
static const char* STR_ME_REMOVE_STAKE = "Remove stake";

// Items names
static const char* STR_IT_dest = "Dest";
static const char* STR_IT_amount = "Amount";
static const char* STR_IT_keep_alive = "Keep alive";

static const char* STR_IT_hotkey = "Hotkey";
static const char* STR_IT_amount_staked = "Amount staked";
static const char* STR_IT_amount_unstaked = "Amount unstaked";

#ifdef __cplusplus
}
#endif
