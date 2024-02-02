/*
 * teek_client_type.h
 *
 * define exported structures
 *
 * Copyright (C) 2022 Huawei Technologies Co., Ltd.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */
#ifndef TEE_CLIENT_TYPE_H
#define TEE_CLIENT_TYPE_H

#include <linux/list.h>
#include "teek_client_constants.h"

#ifndef NULL
#define NULL 0
#endif

struct teec_uuid {
	uint32_t time_low;
	uint16_t time_mid;
	uint16_t timehi_and_version;
	uint8_t clockseq_and_node[8];
};

struct teec_context {
	void *dev;
	uint8_t *ta_path;
	struct list_head shrd_mem_list;
};

struct teec_session {
	uint32_t session_id;
	struct teec_uuid service_id;
	uint32_t ops_cnt;
	struct teec_context *context;
};

struct teec_sharedmemory {
	void *buffer;
	uint32_t size;
	uint32_t flags;
	uint32_t ops_cnt;
	bool is_allocated;
	struct list_head head;
	struct teec_context *context;
};

struct teec_tempmemory_reference {
	void *buffer;
	uint32_t size;
};

struct teec_registeredmemory_reference {
	struct teec_sharedmemory *parent;
	uint32_t size;
	uint32_t offset;
};


struct teec_value {
	uint32_t a;
	uint32_t b;
};

struct teec_ion_reference {
	int ion_share_fd;
	uint32_t ion_size;
};

union teec_parameter {
	struct teec_tempmemory_reference tmpref;
	struct teec_registeredmemory_reference memref;
	struct teec_value value;
	struct teec_ion_reference ionref;
};

struct teec_tui_parameter {
	uint32_t event_type;
	/* tui event type */
	uint32_t value;
	/* return value, is keycode if tui event is getkeycode */
	uint32_t notch;  		/* notch size of phone */
	uint32_t width;  		/* width of foldable screen */
	uint32_t height; 		/* height of foldable screen */
	uint32_t fold_state;	/* state of foldable screen */
	uint32_t display_state; /* one state of folded state */
	uint32_t phy_width;	 	/* real width of the mobile */
	uint32_t phy_height;	/* real height of the mobile */
};

struct teec_operation {
	uint32_t started;
	uint32_t paramtypes;
	union teec_parameter params[4]; /* GP has four params */
	struct teec_session *session;
	bool cancel_flag;
};

typedef uint32_t TEEC_Result;

typedef struct teec_uuid TEEC_UUID;

typedef struct teec_context TEEC_Context;

typedef struct teec_session TEEC_Session;

typedef struct teec_sharedmemory TEEC_SharedMemory;

typedef struct teec_tempmemory_reference TEEC_TempMemoryReference;

typedef struct teec_registeredmemory_reference TEEC_RegisteredMemoryReference;

typedef struct teec_value TEEC_Value;

typedef struct teec_ion_reference TEEC_IonReference;

typedef union teec_parameter TEEC_Parameter;

typedef struct teec_tui_parameter TEEC_TUI_Parameter;

typedef struct {
	uint32_t started;
	uint32_t paramTypes;
	TEEC_Parameter params[4];
	TEEC_Session *session;
	bool cancel_flag;
} TEEC_Operation;

#endif