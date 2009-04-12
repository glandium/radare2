/* radare - LGPL - Copyright 2009 nibble<.ds@gmail.com>, pancake<@nopcode.org> */

#include <stdio.h>
#include <string.h>

#include <r_types.h>
#include <r_lib.h>
#include <r_bininfo.h>
#include "../config.h"

static struct r_bininfo_handle_t *bininfo_static_plugins[] = 
	{ R_BININFO_STATIC_PLUGINS };

struct r_bininfo_t *r_bininfo_new()
{
	struct r_bininfo_t *bin = MALLOC_STRUCT(struct r_bininfo_t);
	r_bininfo_init(bin);
	return bin;
}

void r_bininfo_free(struct r_bininfo_t *bin)
{
	free(bin);
}

int r_bininfo_init(struct r_bininfo_t *bin)
{
	int i;
	bin->cur = NULL;
	bin->user = NULL;
	bin->path = NULL;
	bin->file = NULL;
	bin->rw = 0;
	INIT_LIST_HEAD(&bin->bins);
	for(i=0;bininfo_static_plugins[i];i++)
		r_bininfo_add(bin, bininfo_static_plugins[i]);
	return R_TRUE;
}

void r_bininfo_set_user_ptr(struct r_bininfo_t *bin, void *user)
{
	bin->user = user;
}

int r_bininfo_add(struct r_bininfo_t *bin, struct r_bininfo_handle_t *foo)
{
	struct list_head *pos;
	if (foo->init)
		foo->init(bin->user);
	/* avoid dupped plugins */
	list_for_each_prev(pos, &bin->bins) {
		struct r_bininfo_handle_t *h = list_entry(pos, struct r_bininfo_handle_t, list);
		if (!strcmp(h->name, foo->name))
			return R_FALSE;
	}
	list_add_tail(&(foo->list), &(bin->bins));
	return R_TRUE;
}

int r_bininfo_list(struct r_bininfo_t *bin)
{
	struct list_head *pos;
	list_for_each_prev(pos, &bin->bins) {
		struct r_bininfo_handle_t *h = list_entry(pos, struct r_bininfo_handle_t, list);
		printf(" %s: %s\n", h->name, h->desc);
	}
	return R_FALSE;
}

int r_bininfo_get_line(struct r_bininfo_t *bin, u64 addr, char *file, int len, int *line)
{
	if (bin&&bin->cur&&bin->cur->get_line)
		return bin->cur->get_line(bin, addr, file, len, line);
	return R_FALSE;
}

char *r_bininfo_get_file_line(struct r_bininfo_t *bin, const char *file, int line)
{
	char *linestr;
	char path[1024];
	sprintf(path, "%s/%s", bin->path, file);
	linestr = r_file_slurp_line(path, line, 1);
	return linestr;
}

char *r_bininfo_get_source_path(struct r_bininfo_t *bin)
{
	if (bin->path == NULL) {
		if (bin&&bin->cur&&bin->cur->get_path) {
			bin->path = bin->cur->get_path(bin);
		}
	}
	return bin->path;
}

int r_bininfo_set_source_path(struct r_bininfo_t *bi, char *path)
{
	free(bi->path);
	bi->path = strdup(path);
	return R_TRUE;
}

int r_bininfo_open(struct r_bininfo_t *bin, const char *file, int rw, char *plugin_name)
{
	if (file != NULL)
		bin->file = strdup(file);
	else return R_FALSE;
	bin->rw = rw;

	struct list_head *pos;
	list_for_each_prev(pos, &bin->bins) {
		struct r_bininfo_handle_t *h = list_entry(pos, struct r_bininfo_handle_t, list);
		if ((plugin_name && !strcmp(h->name, plugin_name)) ||
			(h->check && h->check(bin))) 
			bin->cur = h;
	}

	if (bin->cur && bin->cur->open)
		return bin->cur->open(bin);
	
	return R_FALSE;
}

int r_bininfo_close(struct r_bininfo_t *bin)
{
	if (bin->cur && bin->cur->close)
		return bin->cur->close(bin);
	
	return R_FALSE;
}