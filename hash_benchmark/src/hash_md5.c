/**
 * Hash Benchmark Library - MD5 Implementation
 * Extracted and adapted from hashcat
 * License: MIT
 */

#include "../include/hash_md5.h"
#include <string.h>

void md5_transform(const u32 *w0, const u32 *w1, const u32 *w2, const u32 *w3, u32 *digest)
{
  u32 a = digest[0];
  u32 b = digest[1];
  u32 c = digest[2];
  u32 d = digest[3];

  u32 w0_t = w0[0];
  u32 w1_t = w0[1];
  u32 w2_t = w0[2];
  u32 w3_t = w0[3];
  u32 w4_t = w1[0];
  u32 w5_t = w1[1];
  u32 w6_t = w1[2];
  u32 w7_t = w1[3];
  u32 w8_t = w2[0];
  u32 w9_t = w2[1];
  u32 wa_t = w2[2];
  u32 wb_t = w2[3];
  u32 wc_t = w3[0];
  u32 wd_t = w3[1];
  u32 we_t = w3[2];
  u32 wf_t = w3[3];

  MD5_STEP(MD5_F, a, b, c, d, w0_t, MD5C04, MD5S00);
  MD5_STEP(MD5_F, d, a, b, c, w1_t, MD5C05, MD5S01);
  MD5_STEP(MD5_F, c, d, a, b, w2_t, MD5C06, MD5S02);
  MD5_STEP(MD5_F, b, c, d, a, w3_t, MD5C07, MD5S03);
  MD5_STEP(MD5_F, a, b, c, d, w4_t, MD5C08, MD5S00);
  MD5_STEP(MD5_F, d, a, b, c, w5_t, MD5C09, MD5S01);
  MD5_STEP(MD5_F, c, d, a, b, w6_t, MD5C0a, MD5S02);
  MD5_STEP(MD5_F, b, c, d, a, w7_t, MD5C0b, MD5S03);
  MD5_STEP(MD5_F, a, b, c, d, w8_t, MD5C0c, MD5S00);
  MD5_STEP(MD5_F, d, a, b, c, w9_t, MD5C0d, MD5S01);
  MD5_STEP(MD5_F, c, d, a, b, wa_t, MD5C0e, MD5S02);
  MD5_STEP(MD5_F, b, c, d, a, wb_t, MD5C0f, MD5S03);
  MD5_STEP(MD5_F, a, b, c, d, wc_t, MD5C10, MD5S00);
  MD5_STEP(MD5_F, d, a, b, c, wd_t, MD5C11, MD5S01);
  MD5_STEP(MD5_F, c, d, a, b, we_t, MD5C12, MD5S02);
  MD5_STEP(MD5_F, b, c, d, a, wf_t, MD5C13, MD5S03);

  MD5_STEP(MD5_G, a, b, c, d, w1_t, MD5C14, MD5S10);
  MD5_STEP(MD5_G, d, a, b, c, w6_t, MD5C15, MD5S11);
  MD5_STEP(MD5_G, c, d, a, b, wb_t, MD5C16, MD5S12);
  MD5_STEP(MD5_G, b, c, d, a, w0_t, MD5C17, MD5S13);
  MD5_STEP(MD5_G, a, b, c, d, w5_t, MD5C18, MD5S10);
  MD5_STEP(MD5_G, d, a, b, c, wa_t, MD5C19, MD5S11);
  MD5_STEP(MD5_G, c, d, a, b, wf_t, MD5C1a, MD5S12);
  MD5_STEP(MD5_G, b, c, d, a, w4_t, MD5C1b, MD5S13);
  MD5_STEP(MD5_G, a, b, c, d, w9_t, MD5C1c, MD5S10);
  MD5_STEP(MD5_G, d, a, b, c, we_t, MD5C1d, MD5S11);
  MD5_STEP(MD5_G, c, d, a, b, w3_t, MD5C1e, MD5S12);
  MD5_STEP(MD5_G, b, c, d, a, w8_t, MD5C1f, MD5S13);
  MD5_STEP(MD5_G, a, b, c, d, wd_t, MD5C20, MD5S10);
  MD5_STEP(MD5_G, d, a, b, c, w2_t, MD5C21, MD5S11);
  MD5_STEP(MD5_G, c, d, a, b, w7_t, MD5C22, MD5S12);
  MD5_STEP(MD5_G, b, c, d, a, wc_t, MD5C23, MD5S13);

  u32 t;
  MD5_STEP(MD5_H, a, b, c, d, w5_t, MD5C24, MD5S20);
  MD5_STEP(MD5_H, d, a, b, c, w8_t, MD5C25, MD5S21);
  MD5_STEP(MD5_H, c, d, a, b, wb_t, MD5C26, MD5S22);
  MD5_STEP(MD5_H, b, c, d, a, we_t, MD5C27, MD5S23);
  MD5_STEP(MD5_H, a, b, c, d, w1_t, MD5C28, MD5S20);
  MD5_STEP(MD5_H, d, a, b, c, w4_t, MD5C29, MD5S21);
  MD5_STEP(MD5_H, c, d, a, b, w7_t, MD5C2a, MD5S22);
  MD5_STEP(MD5_H, b, c, d, a, wa_t, MD5C2b, MD5S23);
  MD5_STEP(MD5_H, a, b, c, d, wd_t, MD5C2c, MD5S20);
  MD5_STEP(MD5_H, d, a, b, c, w0_t, MD5C2d, MD5S21);
  MD5_STEP(MD5_H, c, d, a, b, w3_t, MD5C2e, MD5S22);
  MD5_STEP(MD5_H, b, c, d, a, w6_t, MD5C2f, MD5S23);
  MD5_STEP(MD5_H, a, b, c, d, w9_t, MD5C30, MD5S20);
  MD5_STEP(MD5_H, d, a, b, c, wc_t, MD5C31, MD5S21);
  MD5_STEP(MD5_H, c, d, a, b, wf_t, MD5C32, MD5S22);
  MD5_STEP(MD5_H, b, c, d, a, w2_t, MD5C33, MD5S23);

  MD5_STEP(MD5_I, a, b, c, d, w0_t, MD5C34, MD5S30);
  MD5_STEP(MD5_I, d, a, b, c, w7_t, MD5C35, MD5S31);
  MD5_STEP(MD5_I, c, d, a, b, we_t, MD5C36, MD5S32);
  MD5_STEP(MD5_I, b, c, d, a, w5_t, MD5C37, MD5S33);
  MD5_STEP(MD5_I, a, b, c, d, wc_t, MD5C38, MD5S30);
  MD5_STEP(MD5_I, d, a, b, c, w3_t, MD5C39, MD5S31);
  MD5_STEP(MD5_I, c, d, a, b, wa_t, MD5C3a, MD5S32);
  MD5_STEP(MD5_I, b, c, d, a, w1_t, MD5C3b, MD5S33);
  MD5_STEP(MD5_I, a, b, c, d, w8_t, MD5C3c, MD5S30);
  MD5_STEP(MD5_I, d, a, b, c, wf_t, MD5C3d, MD5S31);
  MD5_STEP(MD5_I, c, d, a, b, w6_t, MD5C3e, MD5S32);
  MD5_STEP(MD5_I, b, c, d, a, wd_t, MD5C3f, MD5S33);
  MD5_STEP(MD5_I, a, b, c, d, w4_t, MD5C40, MD5S30);
  MD5_STEP(MD5_I, d, a, b, c, wb_t, MD5C41, MD5S31);
  MD5_STEP(MD5_I, c, d, a, b, w2_t, MD5C42, MD5S32);
  MD5_STEP(MD5_I, b, c, d, a, w9_t, MD5C43, MD5S33);

  digest[0] += a;
  digest[1] += b;
  digest[2] += c;
  digest[3] += d;
}

void md5_init(md5_ctx_t *ctx)
{
  ctx->h[0] = MD5C00;
  ctx->h[1] = MD5C01;
  ctx->h[2] = MD5C02;
  ctx->h[3] = MD5C03;

  ctx->w0[0] = 0;
  ctx->w0[1] = 0;
  ctx->w0[2] = 0;
  ctx->w0[3] = 0;
  ctx->w1[0] = 0;
  ctx->w1[1] = 0;
  ctx->w1[2] = 0;
  ctx->w1[3] = 0;
  ctx->w2[0] = 0;
  ctx->w2[1] = 0;
  ctx->w2[2] = 0;
  ctx->w2[3] = 0;
  ctx->w3[0] = 0;
  ctx->w3[1] = 0;
  ctx->w3[2] = 0;
  ctx->w3[3] = 0;

  ctx->len = 0;
}

void md5_update_64(md5_ctx_t *ctx, const u32 *w0, const u32 *w1, const u32 *w2, const u32 *w3, const int len)
{
  if (len == 0) return;

  const int pos = ctx->len & 63;
  const int new_len = pos + len;

  if (new_len < 64)
  {
    switch (pos / 4)
    {
      case 0:
        switch (pos % 4)
        {
          case 0: ctx->w0[0] |= w0[0] << ( 0); break;
          case 1: ctx->w0[0] |= w0[0] << ( 8); break;
          case 2: ctx->w0[0] |= w0[0] << (16); break;
          case 3: ctx->w0[0] |= w0[0] << (24); break;
        }
        break;
      // ... (similar cases for other positions)
    }
  }
  else
  {
    md5_transform(ctx->w0, ctx->w1, ctx->w2, ctx->w3, ctx->h);
    
    ctx->w0[0] = w0[0];
    ctx->w0[1] = w0[1];
    ctx->w0[2] = w0[2];
    ctx->w0[3] = w0[3];
    ctx->w1[0] = w1[0];
    ctx->w1[1] = w1[1];
    ctx->w1[2] = w1[2];
    ctx->w1[3] = w1[3];
    ctx->w2[0] = w2[0];
    ctx->w2[1] = w2[1];
    ctx->w2[2] = w2[2];
    ctx->w2[3] = w2[3];
    ctx->w3[0] = w3[0];
    ctx->w3[1] = w3[1];
    ctx->w3[2] = w3[2];
    ctx->w3[3] = w3[3];
  }

  ctx->len += len;
}

void md5_update(md5_ctx_t *ctx, const u8 *input, const int len)
{
  if (len == 0) return;

  const int pos = ctx->len & 63;
  const int new_len = pos + len;

  if (new_len < 64)
  {
    for (int i = 0; i < len; i++)
    {
      const int idx = (pos + i) / 4;
      const int off = (pos + i) % 4;
      
      u32 *w = NULL;
      if (idx < 4) w = &ctx->w0[idx];
      else if (idx < 8) w = &ctx->w1[idx - 4];
      else if (idx < 12) w = &ctx->w2[idx - 8];
      else w = &ctx->w3[idx - 12];
      
      *w |= ((u32)input[i]) << (off * 8);
    }
  }
  else
  {
    // Handle block boundary crossing
    int remaining = len;
    int offset = 0;
    
    // Fill current block
    int fill = 64 - pos;
    for (int i = 0; i < fill; i++)
    {
      const int idx = (pos + i) / 4;
      const int off = (pos + i) % 4;
      
      u32 *w = NULL;
      if (idx < 4) w = &ctx->w0[idx];
      else if (idx < 8) w = &ctx->w1[idx - 4];
      else if (idx < 12) w = &ctx->w2[idx - 8];
      else w = &ctx->w3[idx - 12];
      
      *w |= ((u32)input[i]) << (off * 8);
    }
    
    md5_transform(ctx->w0, ctx->w1, ctx->w2, ctx->w3, ctx->h);
    
    remaining -= fill;
    offset += fill;
    
    // Process complete blocks
    while (remaining >= 64)
    {
      u32 w0[4], w1[4], w2[4], w3[4];
      memcpy(w0, input + offset, 16);
      memcpy(w1, input + offset + 16, 16);
      memcpy(w2, input + offset + 32, 16);
      memcpy(w3, input + offset + 48, 16);
      
      md5_transform(w0, w1, w2, w3, ctx->h);
      
      remaining -= 64;
      offset += 64;
    }
    
    // Handle remaining bytes
    memset(ctx->w0, 0, 16);
    memset(ctx->w1, 0, 16);
    memset(ctx->w2, 0, 16);
    memset(ctx->w3, 0, 16);
    
    for (int i = 0; i < remaining; i++)
    {
      const int idx = i / 4;
      const int off = i % 4;
      
      u32 *w = NULL;
      if (idx < 4) w = &ctx->w0[idx];
      else if (idx < 8) w = &ctx->w1[idx - 4];
      else if (idx < 12) w = &ctx->w2[idx - 8];
      else w = &ctx->w3[idx - 12];
      
      *w |= ((u32)input[offset + i]) << (off * 8);
    }
  }

  ctx->len += len;
}

void md5_final(md5_ctx_t *ctx, u8 *digest)
{
  const int pos = ctx->len & 63;
  const int idx = pos / 4;
  const int off = pos % 4;
  
  // Add padding bit
  u32 *w = NULL;
  if (idx < 4) w = &ctx->w0[idx];
  else if (idx < 8) w = &ctx->w1[idx - 4];
  else if (idx < 12) w = &ctx->w2[idx - 8];
  else w = &ctx->w3[idx - 12];
  
  *w |= 0x80 << (off * 8);
  
  // If no room for length, process block and start new one
  if (pos >= 56)
  {
    md5_transform(ctx->w0, ctx->w1, ctx->w2, ctx->w3, ctx->h);
    
    memset(ctx->w0, 0, 16);
    memset(ctx->w1, 0, 16);
    memset(ctx->w2, 0, 16);
    memset(ctx->w3, 0, 16);
  }
  
  // Add length in bits
  u64 len_bits = (u64)ctx->len * 8;
  ctx->w3[2] = (u32)(len_bits);
  ctx->w3[3] = (u32)(len_bits >> 32);
  
  md5_transform(ctx->w0, ctx->w1, ctx->w2, ctx->w3, ctx->h);
  
  // Copy result to output
  memcpy(digest, ctx->h, 16);
}

void md5_hash(const u8 *input, int len, u8 *digest)
{
  md5_ctx_t ctx;
  md5_init(&ctx);
  md5_update(&ctx, input, len);
  md5_final(&ctx, digest);
}