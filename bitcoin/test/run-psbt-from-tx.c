#include "config.h"
#include "../psbt.c"
#include "../tx.c"
#include "../../wire/towire.c"
#include "../../wire/fromwire.c"
#include <assert.h>
#include <ccan/cast/cast.h>
#include <common/setup.h>
#include <stdio.h>

/* AUTOGENERATED MOCKS START */
/* Generated stub for amount_asset_is_main */
bool amount_asset_is_main(struct amount_asset *asset UNNEEDED)
{ fprintf(stderr, "amount_asset_is_main called!\n"); abort(); }
/* Generated stub for amount_asset_to_sat */
struct amount_sat amount_asset_to_sat(struct amount_asset *asset UNNEEDED)
{ fprintf(stderr, "amount_asset_to_sat called!\n"); abort(); }
/* Generated stub for amount_feerate */
 bool amount_feerate(u32 *feerate UNNEEDED, struct amount_sat fee UNNEEDED, size_t weight UNNEEDED)
{ fprintf(stderr, "amount_feerate called!\n"); abort(); }
/* Generated stub for amount_sat */
struct amount_sat amount_sat(u64 satoshis UNNEEDED)
{ fprintf(stderr, "amount_sat called!\n"); abort(); }
/* Generated stub for amount_sat_add */
 bool amount_sat_add(struct amount_sat *val UNNEEDED,
				       struct amount_sat a UNNEEDED,
				       struct amount_sat b UNNEEDED)
{ fprintf(stderr, "amount_sat_add called!\n"); abort(); }
/* Generated stub for amount_sat_eq */
bool amount_sat_eq(struct amount_sat a UNNEEDED, struct amount_sat b UNNEEDED)
{ fprintf(stderr, "amount_sat_eq called!\n"); abort(); }
/* Generated stub for amount_sat_greater_eq */
bool amount_sat_greater_eq(struct amount_sat a UNNEEDED, struct amount_sat b UNNEEDED)
{ fprintf(stderr, "amount_sat_greater_eq called!\n"); abort(); }
/* Generated stub for amount_sat_sub */
 bool amount_sat_sub(struct amount_sat *val UNNEEDED,
				       struct amount_sat a UNNEEDED,
				       struct amount_sat b UNNEEDED)
{ fprintf(stderr, "amount_sat_sub called!\n"); abort(); }
/* Generated stub for amount_sat_to_asset */
struct amount_asset amount_sat_to_asset(struct amount_sat *sat UNNEEDED, const u8 *asset UNNEEDED)
{ fprintf(stderr, "amount_sat_to_asset called!\n"); abort(); }
/* Generated stub for amount_tx_fee */
struct amount_sat amount_tx_fee(u32 fee_per_kw UNNEEDED, size_t weight UNNEEDED)
{ fprintf(stderr, "amount_tx_fee called!\n"); abort(); }
/* Generated stub for fromwire_sha256_double */
void fromwire_sha256_double(const u8 **cursor UNNEEDED, size_t *max UNNEEDED,
			    struct sha256_double *sha256d UNNEEDED)
{ fprintf(stderr, "fromwire_sha256_double called!\n"); abort(); }
/* Generated stub for is_anchor_witness_script */
bool is_anchor_witness_script(const u8 *script UNNEEDED, size_t script_len UNNEEDED)
{ fprintf(stderr, "is_anchor_witness_script called!\n"); abort(); }
/* Generated stub for is_to_remote_anchored_witness_script */
bool is_to_remote_anchored_witness_script(const u8 *script UNNEEDED, size_t script_len UNNEEDED)
{ fprintf(stderr, "is_to_remote_anchored_witness_script called!\n"); abort(); }
/* Generated stub for pubkey_to_der */
void pubkey_to_der(u8 der[PUBKEY_CMPR_LEN] UNNEEDED, const struct pubkey *key UNNEEDED)
{ fprintf(stderr, "pubkey_to_der called!\n"); abort(); }
/* Generated stub for pubkey_to_hash160 */
void pubkey_to_hash160(const struct pubkey *pk UNNEEDED, struct ripemd160 *hash UNNEEDED)
{ fprintf(stderr, "pubkey_to_hash160 called!\n"); abort(); }
/* Generated stub for scriptpubkey_p2wsh */
u8 *scriptpubkey_p2wsh(const tal_t *ctx UNNEEDED, const u8 *witnessscript UNNEEDED)
{ fprintf(stderr, "scriptpubkey_p2wsh called!\n"); abort(); }
/* Generated stub for sha256_double */
void sha256_double(struct sha256_double *shadouble UNNEEDED, const void *p UNNEEDED, size_t len UNNEEDED)
{ fprintf(stderr, "sha256_double called!\n"); abort(); }
/* Generated stub for signature_from_der */
bool signature_from_der(const u8 *der UNNEEDED, size_t len UNNEEDED, struct bitcoin_signature *sig UNNEEDED)
{ fprintf(stderr, "signature_from_der called!\n"); abort(); }
/* Generated stub for signature_to_der */
size_t signature_to_der(u8 der[73] UNNEEDED, const struct bitcoin_signature *sig UNNEEDED)
{ fprintf(stderr, "signature_to_der called!\n"); abort(); }
/* Generated stub for towire_sha256_double */
void towire_sha256_double(u8 **pptr UNNEEDED, const struct sha256_double *sha256d UNNEEDED)
{ fprintf(stderr, "towire_sha256_double called!\n"); abort(); }
/* Generated stub for varint_put */
size_t varint_put(u8 buf[VARINT_MAX_LEN] UNNEEDED, varint_t v UNNEEDED)
{ fprintf(stderr, "varint_put called!\n"); abort(); }
/* Generated stub for varint_size */
size_t varint_size(varint_t v UNNEEDED)
{ fprintf(stderr, "varint_size called!\n"); abort(); }
/* AUTOGENERATED MOCKS END */

/* This transaction has scriptSig data in it.
 * We expect that creating a new psbt from it will correctly
 * populate the PSBT object */
static const char *raw_tx = "0200000000010151d12aa54cc6e59a6a92325a8315e93361d9805115a13aa5ba8dbcf30ffd858c000000001716001401fad90abcd66697e2592164722de4a95ebee165fdffffff02603c250200000000160014c2ccab171c2a5be9dab52ec41b825863024c546600093d00000000002200205b8cd3b914cf67cdd8fa6273c930353dd36476734fbd962102c2df53b90880cd02473044022001e73b1745d775521c758e70549ad79b1d076efc34303f416e66ff630f6088e402207b0aa44b35329ae4733463bc9f6ca433c5595f00a902a21c941945a24f8aa577012103d745445c9362665f22e0d96e9e766f273f3260dea39c8a76bfa05dd2684ddccf66000000";

int main(int argc, char *argv[])
{
	struct bitcoin_tx *tx, *tx2;
	u8 *msg;
	size_t len;

	common_setup(argv[0]);
	chainparams = chainparams_for_network("bitcoin");

	msg = tal_arr(tmpctx, u8, 0);
	tx = bitcoin_tx_from_hex(tmpctx, raw_tx, strlen(raw_tx));

	/* convert to wire format */
	towire_bitcoin_tx(&msg, tx);

	len = tal_bytelen(msg);
	assert(len > 0);

	tx2 = fromwire_bitcoin_tx(tmpctx,
				  cast_const2(const u8 **, &msg), &len);
	assert(tx2 != NULL);

	/* Witness/scriptsig data is saved down into psbt */
	assert(tx2->psbt->num_inputs == 1);
	const struct wally_map_item *final_scriptsig = wally_map_get_integer(&tx2->psbt->inputs[0].psbt_fields, /* PSBT_IN_FINAL_SCRIPTSIG */ 0x07);
	assert(final_scriptsig->value_len > 0);
	assert(tx2->psbt->inputs[0].final_witness != NULL);
	audit_psbt(tx2->psbt, tx2->psbt);

	common_shutdown();
	return 0;
}
