/* Copyright (c) 2006-2014 Jonas Fonseca <jonas.fonseca@gmail.com>
#include "request.h"
#include "line.h"
#include "keys.h"
#include "view.h"
#include "repo.h"
		return width * VSPLIT_SCALE > (height - 1) * 2;
		info = find_line_info(argv[0], strlen(argv[0]), FALSE);
		info = get_line_info(index);
	view->width  = apply_step(VSPLIT_SCALE, base->width);
	if (!view_has_flags(view, VIEW_NO_GIT_DIR) && !repo.git_dir[0]) {
	open_external_viewer(mergetool_argv, repo.cdup, TRUE, "");
	if (!open_external_viewer(editor_argv, repo.cdup, TRUE, EDITOR_LINENO_MSG))
		const int len = get_line_info(LINE_DIFF_HEADER)->linelen;
	if (!io_run(&io, IO_RD, repo.cdup, opt_env, blame_argv))
	bool has_path = file && string_format(path, "%s%s", repo.cdup, file);
struct help_request_iterator {
	struct view *view;
	struct keymap *keymap;
	bool add_title;
	const char *group;
};
static bool
help_open_keymap(void *data, const struct request_info *req_info, const char *group)
{
	struct help_request_iterator *iterator = data;
	struct view *view = iterator->view;
	struct keymap *keymap = iterator->keymap;
	const char *key = get_keys(keymap, req_info->request, TRUE);
	if (req_info->request == REQ_NONE || !key || !*key)
		return TRUE;
	if (iterator->add_title && help_open_keymap_title(view, keymap))
		return FALSE;
	iterator->add_title = FALSE;
	if (iterator->group != group) {
		add_line_text(view, group, LINE_HELP_GROUP);
		iterator->group = group;
	add_line_format(view, LINE_DEFAULT, "    %-25s %-20s %s", key,
			enum_name(*req_info), req_info->help);
	return TRUE;
}

static void
help_open_keymap_run_requests(struct help_request_iterator *iterator)
{
	struct view *view = iterator->view;
	struct keymap *keymap = iterator->keymap;
	char buf[SIZEOF_STR];
	const char *group = "External commands:";
	int i;
	for (i = 0; TRUE; i++) {
		if (!req)
			break;

		if (req->keymap != keymap)
		if (iterator->add_title && help_open_keymap_title(view, keymap))
		iterator->add_title = FALSE;
	for (keymap = get_keymaps(); keymap; keymap = keymap->next) {
		struct help_request_iterator iterator = { view, keymap, TRUE };

		if (foreach_request(help_open_keymap, &iterator))
			help_open_keymap_run_requests(&iterator);
	}
		if (!begin_update(view, repo.cdup, log_file, OPEN_EXTRA)) {
		pos = strrchr(text, '\t');
	if (view->lines == 0 && repo.prefix[0]) {
		char *pos = repo.prefix;
	return begin_update(view, repo.cdup, tree_argv, flags);
	const char *file_argv[] = { repo.cdup, opt_file , NULL };
	if (!view->prev && *repo.prefix && !(flags & (OPEN_RELOAD | OPEN_REFRESH))) {
		if (!string_format(opt_file, "%s%s", repo.prefix, path)) {
	if (*opt_ref || !begin_update(view, repo.cdup, file_argv, flags)) {
		if (!begin_update(view, repo.cdup, blame_cat_file_argv, flags))
		if (view->lines == 0 || !begin_update(view, repo.cdup, blame_argv, OPEN_EXTRA)) {
	if (!io_run(&io, IO_RD, repo.cdup, opt_env, argv))
	"git", "ls-files", "-z", "--others", "--exclude-standard", repo.prefix, NULL, NULL,
		char *head = repo.head;
		if (!string_format(buf, "%s/%s", repo.git_dir, paths[i][0]) ||
		if (!*repo.head) {
			if (io_open(&io, "%s/rebase-merge/head-name", repo.git_dir) &&
			string_copy(status_onbranch, repo.head);
	if (repo.is_inside_work_tree == FALSE) {
		return io_run(io, IO_WR, repo.cdup, opt_env, staged_argv);
		return io_run(io, IO_WR, repo.cdup, opt_env, others_argv);
			if (!io_run_fg(reset_argv, repo.cdup))
		return io_run_fg(checkout_argv, repo.cdup);
	if (!io_run(&io, IO_WR, repo.cdup, opt_env, apply_argv))
	static const char *file_argv[] = { repo.cdup, stage_status.new.name, NULL };
	view->dir = repo.cdup;
		if (!state->added_changes_commits && opt_show_changes && repo.is_inside_work_tree)
		string_ncopy(repo.remote, value, valuelen);
	} else if (*repo.remote && !strcmp(name, ".merge")) {
		size_t from = strlen(repo.remote);
		if (!string_format_from(repo.remote, &from, "/%s", value))
			repo.remote[0] = 0;
	if (chdir(repo.git_dir) < 0)
		die("Failed to chdir(%s): %s", repo.git_dir, strerror(errno));
	if (!getcwd(repo.git_dir, sizeof(repo.git_dir)))
	if (setenv("GIT_DIR", repo.git_dir, TRUE))
		die("Failed to set GIT_DIR to '%s'", repo.git_dir);
	repo.is_inside_work_tree = TRUE;
	struct line_info *info = get_line_info(type);
	else if (*repo.head && !prefixcmp(name, "branch.") &&
		 !strncmp(name + 7, repo.head, strlen(repo.head)))
		set_remote_branch(name + 7 + strlen(repo.head), value, valuelen);
	if (!repo.git_dir[0] && request != REQ_VIEW_PAGER)