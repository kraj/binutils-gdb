/* ginsn.h - GAS instruction representation.
   Copyright (C) 2023 Free Software Foundation, Inc.

   This file is part of GAS, the GNU Assembler.

   GAS is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   GAS is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GAS; see the file COPYING.  If not, write to the Free
   Software Foundation, 51 Franklin Street - Fifth Floor, Boston, MA
   02110-1301, USA.  */

#include "as.h"
#include "subsegs.h"
#include "ginsn.h"
#include "scfi.h"

#ifdef TARGET_USE_GINSN

static
ginsnS *ginsn_alloc (void)
{
  ginsnS *ginsn = XCNEW (ginsnS);
  return ginsn;
}

static ginsnS*
ginsn_init (enum ginsn_type type, symbolS *sym, bool real_p)
{
  ginsnS *ginsn = ginsn_alloc ();
  ginsn->type = type;
  ginsn->sym = sym;
  if (real_p)
    ginsn->flags |= GINSN_F_INSN_REAL;
  return ginsn;
}

static void
ginsn_set_src (struct ginsn_src *src, enum ginsn_src_type type, uint32_t reg,
	       int32_t immdisp)
{
  if (!src)
    return;

  src->type = type;
  /* Even when the use-case is SCFI, the value of reg may be > SCFI_NUM_REGS.
     E.g., in AMD64, push fs etc.  */
  src->reg = reg;

  if (type == GINSN_SRC_IMM || type == GINSN_SRC_INDIRECT)
    src->immdisp = immdisp;
}

static void
ginsn_set_dst (struct ginsn_dst *dst, enum ginsn_dst_type type, uint32_t reg,
	       int32_t disp)
{
  if (!dst)
    return;

  dst->type = type;
  dst->reg = reg;

  if (type == GINSN_DST_INDIRECT)
    dst->disp = disp;
}

# if 0
static void
free_ginsn (ginsnS *ginsn)
{
  free (ginsn);
  ginsn = NULL;
}
#endif

struct ginsn_src *
ginsn_get_src1 (ginsnS *ginsn)
{
  return &ginsn->src[0];
}

struct ginsn_src *
ginsn_get_src2 (ginsnS *ginsn)
{
  return &ginsn->src[1];
}

struct ginsn_dst *
ginsn_get_dst (ginsnS *ginsn)
{
  return &ginsn->dst;
}

uint32_t
ginsn_get_src_reg (struct ginsn_src *src)
{
  return src->reg;
}

enum ginsn_src_type
ginsn_get_src_type (struct ginsn_src *src)
{
  return src->type;
}

uint32_t
ginsn_get_src_disp (struct ginsn_src *src)
{
  return src->immdisp;
}

uint32_t
ginsn_get_src_imm (struct ginsn_src *src)
{
  return src->immdisp;
}

uint32_t
ginsn_get_dst_reg (struct ginsn_dst *dst)
{
  return dst->reg;
}

enum ginsn_dst_type
ginsn_get_dst_type (struct ginsn_dst *dst)
{
  return dst->type;
}

int32_t
ginsn_get_dst_disp (struct ginsn_dst *dst)
{
  return (int32_t) dst->disp;
}

void
label_ginsn_map_insert (symbolS *label, ginsnS *ginsn)
{
  const char *name = S_GET_NAME (label);
  str_hash_insert (frchain_now->frch_ginsn_data->label_ginsn_map,
		   name, ginsn, 0 /* noreplace.  */);
}

ginsnS *
label_ginsn_map_find (symbolS *label)
{
  const char *name = S_GET_NAME (label);
  ginsnS *ginsn
    = (ginsnS *) str_hash_find (frchain_now->frch_ginsn_data->label_ginsn_map,
				name);
  return ginsn;
}

ginsnS *
ginsn_new_symbol (symbolS *sym, bool func_begin_p)
{
  ginsnS *ginsn = ginsn_alloc ();
  ginsn->type = GINSN_TYPE_SYMBOL;
  ginsn->sym = sym;
  if (func_begin_p)
    ginsn->flags |= GINSN_F_FUNC_MARKER;
  return ginsn;
}

ginsnS *
ginsn_new_symbol_func_begin (symbolS *sym)
{
  return ginsn_new_symbol (sym, true);
}

ginsnS *
ginsn_new_symbol_func_end (symbolS *sym)
{
  return ginsn_new_symbol (sym, false);
}

ginsnS *
ginsn_new_symbol_user_label (symbolS *sym)
{
  ginsnS *ginsn = ginsn_new_symbol (sym, false);
  ginsn->flags |= GINSN_F_USER_LABEL;
  return ginsn;
}

/* PS: In some of the ginsn_new_* APIs below, a 'uint32_t src[1-2]_val' is
   used to carry even an 'int32_t disp'.  This is done to keep the number
   of arguments in the APIs in check, in hope that this is more readable
   code.  */

ginsnS *
ginsn_new_add (symbolS *sym, bool real_p,
	       enum ginsn_src_type src1_type, uint32_t src1_val,
	       enum ginsn_src_type src2_type, uint32_t src2_val,
	       enum ginsn_dst_type dst_type, uint32_t dst_reg)
{
  ginsnS *ginsn = ginsn_init (GINSN_TYPE_ADD, sym, real_p);
  /* src info.  */
  ginsn_set_src (&ginsn->src[0], src1_type, src1_val, src1_val);
  /* GINSN_SRC_INDIRECT src2_type is not expected.  */
  gas_assert (src2_type != GINSN_SRC_INDIRECT);
  ginsn_set_src (&ginsn->src[1], src2_type, src2_val, src2_val);
  /* dst info.  */
  gas_assert (dst_type != GINSN_DST_INDIRECT);
  ginsn_set_dst (&ginsn->dst, dst_type, dst_reg, 0);

  return ginsn;
}

ginsnS *
ginsn_new_and (symbolS *sym, bool real_p,
	       enum ginsn_src_type src1_type, uint32_t src1_val,
	       enum ginsn_src_type src2_type, uint32_t src2_val,
	       enum ginsn_dst_type dst_type, uint32_t dst_reg)
{
  ginsnS *ginsn = ginsn_init (GINSN_TYPE_AND, sym, real_p);
  /* src info.  */
  ginsn_set_src (&ginsn->src[0], src1_type, src1_val, src1_val);
  /* GINSN_SRC_INDIRECT src2_type is not expected.  */
  gas_assert (src2_type != GINSN_SRC_INDIRECT);
  ginsn_set_src (&ginsn->src[1], src2_type, src2_val, src2_val);
  /* dst info.  */
  gas_assert (dst_type != GINSN_DST_INDIRECT);
  ginsn_set_dst (&ginsn->dst, dst_type, dst_reg, 0);

  return ginsn;
}

ginsnS *
ginsn_new_call (symbolS *sym, bool real_p,
		enum ginsn_src_type src_type, uint32_t src_val,
		symbolS *src_text_sym)

{
  ginsnS *ginsn = ginsn_init (GINSN_TYPE_CALL, sym, real_p);
  /* src info.  */
  ginsn_set_src (&ginsn->src[0], src_type, src_val, 0);

  if (src_type == GINSN_SRC_SYMBOL)
    ginsn->src[0].sym = src_text_sym;

  return ginsn;
}

ginsnS *
ginsn_new_jump (symbolS *sym, bool real_p,
		enum ginsn_src_type src_type, uint32_t src_val,
		symbolS *src_ginsn_sym)
{
  ginsnS *ginsn = ginsn_init (GINSN_TYPE_JUMP, sym, real_p);
  /* src info.  */
  ginsn_set_src (&ginsn->src[0], src_type, src_val, 0);

  if (src_type == GINSN_SRC_SYMBOL)
    ginsn->src[0].sym = src_ginsn_sym;

  return ginsn;
}

ginsnS *
ginsn_new_jump_cond (symbolS *sym, bool real_p,
		     enum ginsn_src_type src_type, uint32_t src_val,
		     symbolS *src_ginsn_sym)
{
  ginsnS *ginsn = ginsn_init (GINSN_TYPE_JUMP_COND, sym, real_p);
  /* src info.  */
  ginsn_set_src (&ginsn->src[0], src_type, src_val, 0);

  if (src_type == GINSN_SRC_SYMBOL)
    ginsn->src[0].sym = src_ginsn_sym;

  return ginsn;
}

ginsnS *
ginsn_new_mov (symbolS *sym, bool real_p,
	       enum ginsn_src_type src_type, uint32_t src_reg, int32_t src_disp,
	       enum ginsn_dst_type dst_type, uint32_t dst_reg, int32_t dst_disp)
{
  ginsnS *ginsn = ginsn_init (GINSN_TYPE_MOV, sym, real_p);
  /* src info.  */
  ginsn_set_src (&ginsn->src[0], src_type, src_reg, src_disp);
  /* dst info.  */
  ginsn_set_dst (&ginsn->dst, dst_type, dst_reg, dst_disp);

  return ginsn;
}

ginsnS *
ginsn_new_store (symbolS *sym, bool real_p,
		 enum ginsn_src_type src_type, uint32_t src_reg,
		 enum ginsn_dst_type dst_type)
{
  ginsnS *ginsn = ginsn_init (GINSN_TYPE_STS, sym, real_p);
  /* src info.  */
  ginsn_set_src (&ginsn->src[0], src_type, src_reg, 0);
  /* dst info.  */
  gas_assert (dst_type == GINSN_DST_STACK || dst_type == GINSN_DST_MEM);
  ginsn_set_dst (&ginsn->dst, dst_type, 0, 0);

  return ginsn;
}

ginsnS *
ginsn_new_load (symbolS *sym, bool real_p,
		enum ginsn_src_type src_type,
		enum ginsn_dst_type dst_type, uint32_t dst_reg)
{
  ginsnS *ginsn = ginsn_init (GINSN_TYPE_LDS, sym, real_p);
  /* src info.  */
  gas_assert (src_type == GINSN_SRC_STACK || src_type == GINSN_SRC_MEM);
  ginsn_set_src (&ginsn->src[0], src_type, 0, 0);
  /* dst info.  */
  ginsn_set_dst (&ginsn->dst, dst_type, dst_reg, 0);

  return ginsn;
}

ginsnS *
ginsn_new_sub (symbolS *sym, bool real_p,
	       enum ginsn_src_type src1_type, uint32_t src1_val,
	       enum ginsn_src_type src2_type, uint32_t src2_val,
	       enum ginsn_dst_type dst_type, uint32_t dst_reg)
{
  ginsnS *ginsn = ginsn_init (GINSN_TYPE_SUB, sym, real_p);
  /* src info.  */
  ginsn_set_src (&ginsn->src[0], src1_type, src1_val, src1_val);
  /* GINSN_SRC_INDIRECT src2_type is not expected.  */
  gas_assert (src2_type != GINSN_SRC_INDIRECT);
  ginsn_set_src (&ginsn->src[1], src2_type, src2_val, src2_val);
  /* dst info.  */
  ginsn_set_dst (&ginsn->dst, dst_type, dst_reg, 0);

  return ginsn;
}

ginsnS *
ginsn_new_other (symbolS *sym, bool real_p,
		 enum ginsn_src_type src1_type, uint32_t src1_val,
		 enum ginsn_src_type src2_type, uint32_t src2_val,
		 enum ginsn_dst_type dst_type, uint32_t dst_reg)
{
  ginsnS *ginsn = ginsn_init (GINSN_TYPE_OTHER, sym, real_p);
  /* src info.  */
  ginsn_set_src (&ginsn->src[0], src1_type, src1_val, src1_val);
  /* GINSN_SRC_INDIRECT src2_type is not expected.  */
  gas_assert (src2_type != GINSN_SRC_INDIRECT);
  ginsn_set_src (&ginsn->src[1], src2_type, src2_val, src2_val);
  /* dst info.  */
  ginsn_set_dst (&ginsn->dst, dst_type, dst_reg, 0);

  return ginsn;
}

ginsnS *
ginsn_new_return (symbolS *sym, bool real_p)
{
  ginsnS *ginsn = ginsn_init (GINSN_TYPE_RETURN, sym, real_p);
  return ginsn;
}

void
ginsn_set_file_line (ginsnS *ginsn, const char *file, unsigned int line)
{
  if (!ginsn)
    return;

  ginsn->file = file;
  ginsn->line = line;
}

int
ginsn_link_next (ginsnS *ginsn, ginsnS *next)
{
  int ret = 0;

  /* Avoid data corruption by limiting the scope of the API.  */
  if (!ginsn || ginsn->next)
    return 1;

  ginsn->next = next;

  return ret;
}

bool
ginsn_track_reg_p (uint32_t dw2reg, enum ginsn_gen_mode gmode)
{
  bool track_p = false;

  if (gmode == GINSN_GEN_SCFI && dw2reg <= SCFI_NUM_REGS)
    {
      /* FIXME - rename this to tc_ ? */
      track_p |= SCFI_CALLEE_SAVED_REG_P(dw2reg);
      track_p |= (dw2reg == REG_FP);
      track_p |= (dw2reg == REG_SP);
    }

  return track_p;
}

static bool
ginsn_indirect_jump_p (ginsnS *ginsn)
{
  bool ret_p = false;
  if (!ginsn)
    return ret_p;

  ret_p = (ginsn->type == GINSN_TYPE_JUMP
	   && ginsn->src[0].type == GINSN_SRC_REG);
  return ret_p;
}

static bool
ginsn_direct_local_jump_p (ginsnS *ginsn)
{
  bool ret_p = false;
  if (!ginsn)
    return ret_p;

  ret_p |= (ginsn->type == GINSN_TYPE_JUMP
	    && ginsn->src[0].type == GINSN_SRC_SYMBOL
	    && S_IS_LOCAL (ginsn->src[0].sym));
  return ret_p;
}

static void
bb_add_edge (gbbS* from_bb, gbbS *to_bb)
{
  gedgeS *tmpedge = NULL;
  gedgeS *gedge;
  bool exists = false;

  if (!from_bb || !to_bb)
    return;

  /* Create a new edge object.  */
  gedge = XCNEW (gedgeS);
  gedge->dst_bb = to_bb;
  gedge->next = NULL;
  gedge->visited = false;

  /* Add it in.  */
  if (from_bb->out_gedges == NULL)
    {
      from_bb->out_gedges = gedge;
      from_bb->num_out_gedges++;
    }
  else
    {
      /* Get the tail of the list.  */
      tmpedge = from_bb->out_gedges;
      while (tmpedge)
	{
	  /* Do not add duplicate edges.  Duplicated edges will cause unwanted
	     failures in the forward and backward passes for SCFI.  */
	  if (tmpedge->dst_bb == to_bb)
	    {
	      exists = true;
	      break;
	    }
	  if (tmpedge->next)
	    tmpedge = tmpedge->next;
	  else
	    break;
	}

      if (!exists)
	{
	  tmpedge->next = gedge;
	  from_bb->num_out_gedges++;
	}
      else
	free (gedge);
    }
}

static void
cfg_add_bb (gcfgS *gcfg, gbbS *gbb)
{
  gbbS *last_bb = NULL;

  if (!gcfg->root_bb)
    gcfg->root_bb = gbb;
  else
    {
      last_bb = gcfg->root_bb;
      while (last_bb->next)
	last_bb = last_bb->next;

      last_bb->next = gbb;
    }
  gcfg->num_gbbs++;

  gbb->id = gcfg->num_gbbs;
}

static gbbS*
add_bb_at_ginsn (gcfgS *gcfg, ginsnS *ginsn, gbbS *prev_bb);

static gbbS*
find_bb (gcfgS *gcfg, ginsnS *ginsn)
{
  gbbS *found_bb = NULL;
  gbbS *gbb = NULL;

  if (!ginsn)
    return found_bb;

  if (ginsn->visited)
    {
      cfg_for_each_bb(gcfg, gbb)
	{
	  if (gbb->first_ginsn == ginsn)
	    {
	      found_bb = gbb;
	      break;
	    }
	}
      /* Must be found if ginsn is visited.  */
      gas_assert (found_bb);
    }

  return found_bb;
}

static gbbS*
find_or_make_bb (gcfgS *gcfg, ginsnS *ginsn, gbbS *prev_bb)
{
  gbbS *found_bb = NULL;

  found_bb = find_bb (gcfg, ginsn);
  if (found_bb)
    return found_bb;

  return add_bb_at_ginsn (gcfg, ginsn, prev_bb);
}

/* Add the basic block starting at GINSN to the given GCFG.
   Also adds an edge from the PREV_BB to the newly added basic block.

   This is a recursive function which returns the root of the added
   basic blocks.  */

static gbbS*
add_bb_at_ginsn (gcfgS *gcfg, ginsnS *ginsn, gbbS *prev_bb)
{
  gbbS *current_bb = NULL;
  ginsnS *gins = NULL;
  symbolS *taken_label;

  while (ginsn)
    {
      /* Skip these as they may be right after a GINSN_TYPE_RETURN.
	 For GINSN_TYPE_RETURN, we have already considered that as
	 end of bb, and a logical exit from function.  */
      if (GINSN_F_FUNC_END_P(ginsn))
	{
	  ginsn = ginsn->next;
	  continue;
	}

      if (ginsn->visited)
	{
	  /* If the ginsn has been visited earlier, the bb must exist by now
	     in the cfg.  */
	  prev_bb = current_bb;
	  current_bb = find_bb (gcfg, ginsn);
	  gas_assert (current_bb);
	  /* Add edge from the prev_bb.  */
	  if (prev_bb)
	    bb_add_edge (prev_bb, current_bb);
	  break;
	}
      else if (current_bb && GINSN_F_USER_LABEL_P(ginsn))
	{
	  /* Create new bb starting at this label ginsn.  */
	  prev_bb = current_bb;
	  find_or_make_bb (gcfg, ginsn, prev_bb);
	  break;
	}

      if (current_bb == NULL)
	{
	  /* Create a new bb.  */
	  current_bb = XCNEW (gbbS);
	  cfg_add_bb (gcfg, current_bb);
	  /* Add edge for the Not Taken, or Fall-through path.  */
	  if (prev_bb)
	    bb_add_edge (prev_bb, current_bb);
	}

      if (current_bb->first_ginsn == NULL)
	current_bb->first_ginsn = ginsn;

      ginsn->visited = true;
      current_bb->num_ginsns++;
      current_bb->last_ginsn = ginsn;

      /* Note that BB is _not_ split on ginsn of type GINSN_TYPE_CALL.  */
      if (ginsn->type == GINSN_TYPE_JUMP
	  || ginsn->type == GINSN_TYPE_JUMP_COND
	  || ginsn->type == GINSN_TYPE_RETURN)
	{
	  /* Indirect Jumps or direct jumps to symbols non-local to the
	     function must not be seen here.  The caller must have already
	     checked for that.  */
	  gas_assert (!ginsn_indirect_jump_p (ginsn));
	  if (ginsn->type == GINSN_TYPE_JUMP)
	    gas_assert (ginsn_direct_local_jump_p (ginsn));

	  /* Direct Jumps.  May include conditional or unconditional change of
	     flow.  What is important for CFG creation is that the target be
	     local to function.  */
	  if (ginsn->type == GINSN_TYPE_JUMP_COND
	      || ginsn_direct_local_jump_p (ginsn))
	    {
	      gas_assert (ginsn->src[0].type == GINSN_SRC_SYMBOL);
	      taken_label = ginsn->src[0].sym;
	      gas_assert (taken_label && S_IS_LOCAL (taken_label));

	      /* Follow the target on the taken path.  */
	      gins = label_ginsn_map_find (taken_label);
	      gas_assert (gins);

	      /* Preserve the prev_bb to be the dominator bb as we are
		 going to follow the taken path of the conditional branch
		 soon.  */
	      prev_bb = current_bb;

	      /* Add the bb for the target of the taken branch.  */
	      find_or_make_bb (gcfg, gins, prev_bb);
	    }
	 else if (ginsn->type == GINSN_TYPE_RETURN)
	   {
	     /* We'll come back to the following ginsns after GINSN_TYPE_RETURN
		from another path if it is indeed reachable code.  */
	     break;
	   }

	 /* Current BB has been processed.  */
	 current_bb = NULL;
	}
      ginsn = ginsn->next;
    }

  return current_bb;
}

static int
gbbs_compare (const void *v1, const void *v2)
{
  const gbbS *bb1 = *(const gbbS **) v1;
  const gbbS *bb2 = *(const gbbS **) v2;

  if (bb1->first_ginsn->id < bb2->first_ginsn->id)
    return -1;
  else if (bb1->first_ginsn->id > bb2->first_ginsn->id)
    return 1;
  else if (bb1->first_ginsn->id == bb2->first_ginsn->id)
    return 0;

  return 0;
}

/* Traverse the list of ginsns for the function and warn if some
   ginsns are not visited.

   FIXME - this code assumes the caller has already performed a pass over
   ginsns such that the reachable ginsns are already marked.  Revisit this - we
   should ideally make this pass self-sufficient.  */

static int
ginsn_pass_warn_unreachable_code (symbolS *func, gcfgS *gcfg ATTRIBUTE_UNUSED,
				  ginsnS *root_ginsn)
{
  ginsnS *ginsn;
  bool unreach_p = false;

  if (!gcfg || !func || !root_ginsn)
    return 0;

  ginsn = root_ginsn;

  while (ginsn)
    {
      /* Some ginsns of type GINSN_TYPE_SYMBOL remain unvisited.  Some
	 may even be excluded from the CFG as they are not reachable, given
	 their function, e.g., user labels after return machine insn.  */
      if (!ginsn->visited
	  && !GINSN_F_FUNC_END_P(ginsn)
	  && !GINSN_F_USER_LABEL_P(ginsn))
	{
	  unreach_p = true;
	  break;
	}
      ginsn = ginsn->next;
    }

  if (unreach_p)
    as_warn_where (ginsn->file, ginsn->line,
		   _("GINSN: found unreachable code in func '%s'"),
		   S_GET_NAME (func));

  return unreach_p;
}

void
gcfg_get_bbs_in_prog_order (gcfgS *gcfg, gbbS **prog_order_bbs)
{
  int i = 0;
  gbbS *gbb;

  if (!prog_order_bbs)
    return;

  cfg_for_each_bb(gcfg, gbb)
    {
      gas_assert (i < gcfg->num_gbbs);
      prog_order_bbs[i++] = gbb;
    }

  qsort (prog_order_bbs, gcfg->num_gbbs, sizeof (gbbS *), gbbs_compare);
}

/* Build the control flow graph for the ginsns of the function.

   It is important that the target adds an appropriate ginsn:
     - GINSN_TYPE_JUMP,
     - GINSN_TYPE_JUMP_COND,
     - GINSN_TYPE_CALL,
     - GINSN_TYPE_RET
  at the associated points in the function.  The correctness of the CFG
  depends on the accuracy of these 'change of flow instructions'.  */

gcfgS *
build_gcfg (void)
{
  gcfgS *gcfg;
  ginsnS *first_ginsn;

  gcfg = XCNEW (gcfgS);
  first_ginsn = frchain_now->frch_ginsn_data->gins_rootP;
  add_bb_at_ginsn (gcfg, first_ginsn, NULL /* prev_bb.  */);

  return gcfg;
}

gbbS *
get_rootbb_gcfg (gcfgS *gcfg)
{
  gbbS *rootbb = NULL;

  if (!gcfg || !gcfg->num_gbbs)
    return NULL;

  rootbb = gcfg->root_bb;

  return rootbb;
}

void
frch_ginsn_data_init (symbolS *func, symbolS *start_addr,
		      enum ginsn_gen_mode gmode)
{
  /* FIXME - error out if prev object is not free'd ?  */
  frchain_now->frch_ginsn_data = XCNEW (struct frch_ginsn_data);

  frchain_now->frch_ginsn_data->mode = gmode;
  /* Annotate with the current function symbol.  */
  frchain_now->frch_ginsn_data->func = func;
  /* Create a new start address symbol now.  */
  frchain_now->frch_ginsn_data->start_addr = start_addr;
  /* Assume the set of ginsn are apt for CFG creation, by default.  */
  frchain_now->frch_ginsn_data->gcfg_apt_p = true;

  frchain_now->frch_ginsn_data->label_ginsn_map = str_htab_create ();
}

void
frch_ginsn_data_cleanup (void)
{
  ginsnS *ginsn = NULL;
  ginsnS *next_ginsn = NULL;

  ginsn = frchain_now->frch_ginsn_data->gins_rootP;
  while (ginsn)
    {
      next_ginsn = ginsn->next;
      free (ginsn);
      ginsn = next_ginsn;
    }

  if (frchain_now->frch_ginsn_data->label_ginsn_map)
    htab_delete (frchain_now->frch_ginsn_data->label_ginsn_map);

  free (frchain_now->frch_ginsn_data);
  frchain_now->frch_ginsn_data = NULL;
}

/* Append GINSN to the list of ginsns for the current function being
   assembled.  */

int
frch_ginsn_data_append (ginsnS *ginsn)
{
  ginsnS *last = NULL;
  ginsnS *temp = NULL;
  uint64_t id = 0;

  if (!ginsn)
    return 1;

  if (frchain_now->frch_ginsn_data->gins_lastP)
    id = frchain_now->frch_ginsn_data->gins_lastP->id;

  /* Do the necessary preprocessing on the set of input GINSNs:
       - Update each ginsn with its ID.
     While you iterate, also keep gcfg_apt_p updated by checking whether any
     ginsn is inappropriate for GCFG creation.  */
  temp = ginsn;
  while (temp)
    {
      temp->id = ++id;

      if (ginsn_indirect_jump_p (temp)
	  || (ginsn->type == GINSN_TYPE_JUMP
	      && !ginsn_direct_local_jump_p (temp)))
	frchain_now->frch_ginsn_data->gcfg_apt_p = false;

      /* The input GINSN may be a linked list of multiple ginsns chained
	 together.  Find the last ginsn in the input chain of ginsns.  */
      last = temp;

      temp = temp->next;
    }

  /* Link in the ginsn to the tail.  */
  if (!frchain_now->frch_ginsn_data->gins_rootP)
    frchain_now->frch_ginsn_data->gins_rootP = ginsn;
  else
    ginsn_link_next (frchain_now->frch_ginsn_data->gins_lastP, ginsn);

  frchain_now->frch_ginsn_data->gins_lastP = last;

  return 0;
}

enum ginsn_gen_mode frch_ginsn_gen_mode (void)
{
  enum ginsn_gen_mode gmode = GINSN_GEN_NONE;

  if (frchain_now->frch_ginsn_data)
    gmode = frchain_now->frch_ginsn_data->mode;

  return gmode;
}

int
ginsn_data_begin (symbolS *func)
{
  ginsnS *ginsn;

  /* The previous block of asm must have been processed by now.  */
  if (frchain_now->frch_ginsn_data)
    as_bad (_("GINSN process for prev func not done"));

  /* FIXME - hard code the mode to GINSN_GEN_SCFI.
     This can be changed later when other passes on ginsns are formalised.  */
  frch_ginsn_data_init (func, symbol_temp_new_now (), GINSN_GEN_SCFI);

  /* Create and insert ginsn with function begin marker.  */
  ginsn = ginsn_new_symbol_func_begin (func);
  frch_ginsn_data_append (ginsn);

  return 0;
}

int
ginsn_data_end (symbolS *label)
{
  ginsnS *ginsn;
  gbbS *root_bb;
  gcfgS *gcfg;
  symbolS *func;

  int ret = 0;

  /* Insert Function end marker.  */
  ginsn = ginsn_new_symbol_func_end (label);
  frch_ginsn_data_append (ginsn);

  func = frchain_now->frch_ginsn_data->func;

  /* Build the cfg of ginsn(s) of the function.  */
  if (!frchain_now->frch_ginsn_data->gcfg_apt_p)
    {
      as_warn (_("Untraceable control flow for func '%s'"), S_GET_NAME (func));
      goto end;
    }

  gcfg = build_gcfg ();

  root_bb = get_rootbb_gcfg (gcfg);
  if (!root_bb)
    {
      as_bad (_("Bad cfg of ginsn of func '%s'"), S_GET_NAME (func));
      goto end;
    }

  /* Synthesize DWARF CFI and emit it.  */
  ret = scfi_synthesize_dw2cfi (func, gcfg, root_bb);
  if (ret)
    goto end;
  scfi_emit_dw2cfi (func);

  /* Other passes, e.g. warn for unreachable code can be enabled too.  */
  ginsn = frchain_now->frch_ginsn_data->gins_rootP;
  ginsn_pass_warn_unreachable_code (func, gcfg, ginsn);

end:
  frch_ginsn_data_cleanup ();
  return ret;
}

/* Add GINSN_TYPE_SYMBOL type ginsn for user-defined labels.  These may be
   branch targets, and hence are necessary for control flow graph.  */

void
ginsn_frob_label (symbolS *label)
{
  ginsnS *label_ginsn;
  symbolS *gsym;
  const char *file;
  unsigned int line;

  if (frchain_now->frch_ginsn_data)
    {
      /* PS: Note how we use the last ginsn's sym for this GINSN_TYPE_SYMBOL
	 ginsn (i.e., skip keeping the actual LABEL symbol as ginsn->sym).
	 We try to avoid keeping GAS symbols in ginsn(s) to avoid inadvertent
	 updates or cleanups.  */
      gsym = frchain_now->frch_ginsn_data->gins_lastP->sym;
      label_ginsn = ginsn_new_symbol_user_label (gsym);
      /* Keep the location updated.  */
      file = as_where (&line);
      ginsn_set_file_line (label_ginsn, file, line);

      frch_ginsn_data_append (label_ginsn);

      label_ginsn_map_insert (label, label_ginsn);
    }
}

#else

int
ginsn_data_begin (symbolS *func ATTRIBUTE_UNUSED)
{
  as_bad (_("ginsn unsupported for target"));
  return 1;
}

int
ginsn_data_end (symbolS *label ATTRIBUTE_UNUSED)
{
  as_bad (_("ginsn unsupported for target"));
  return 1;
}

void
ginsn_frob_label (symbolS *sym ATTRIBUTE_UNUSED)
{
  return;
}

#endif  /* TARGET_USE_GINSN.  */
