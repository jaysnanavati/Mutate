
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "CuTest.h"

#include "bitfield.h"
#include "pwp_connection.h"
#include "bitstream.h"
#include "mock_block_readwriter.h"
#include "mock_piece.h"

//static char* __mock_infohash = "00000000000000000000";
//static char* __mock_peerid = "00000000000000000000";

void TestPWP_init_has_us_choked(
    CuTest * tc
)
{
    void *pc;

    pc = pwp_conn_new(NULL);
    CuAssertTrue(tc, 1 == pwp_conn_im_choked(pc));
}

void TestPWP_init_not_interested(
    CuTest * tc
)
{
    void *pc;

    pc = pwp_conn_new(NULL);
    CuAssertTrue(tc, 0 == pwp_conn_im_interested(pc));
}

/**
 * The peer is recorded as chocked when we set to choked
 * */
void TestPWP_choke_sets_as_choked(
    CuTest * tc
)
{
    void *pc;

    pc = pwp_conn_new(NULL);
    pwp_conn_choke_peer(pc);
    CuAssertTrue(tc, pwp_conn_im_choking(pc));
    pwp_conn_release(pc);
}

void TestPWP_unchoke_sets_as_unchoked(
    CuTest * tc
)
{
    void *pc;

    pc = pwp_conn_new(NULL);
    pwp_conn_choke_peer(pc);
    pwp_conn_unchoke_peer(pc);
    CuAssertTrue(tc, !pwp_conn_im_choking(pc));
    pwp_conn_release(pc);
}

void TestPWP_unchoke_setget_flag(
    CuTest * tc
)
{
    void *pc;

    pc = pwp_conn_new(NULL);
    pwp_conn_set_state(pc, PC_IM_CHOKING | PC_HANDSHAKE_RECEIVED);
    CuAssertTrue(tc, pwp_conn_flag_is_set(pc, PC_IM_CHOKING));
    pwp_conn_release(pc);
}

