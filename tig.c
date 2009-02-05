static size_t utf8_length(const char **string, size_t col, int *width, size_t max_width, int *trimmed, bool reserve);
#define SCROLL_INTERVAL	1
/* Some ASCII-shorthands fitted into the ncurses namespace. */
static size_t
string_expand_length(const char *line, int tabsize)
{
	size_t size, pos;

	for (pos = 0; line[pos]; pos++) {
		if (line[pos] == '\t' && tabsize > 0)
			size += tabsize - (size % tabsize);
		else
			size++;
	}
	return size;
}

static void
string_expand(char *dst, size_t dstlen, const char *src, int tabsize)
{
	size_t size, pos;

	for (size = pos = 0; size < dstlen - 1 && src[pos]; pos++) {
		if (src[pos] == '\t') {
			size_t expanded = tabsize - (size % tabsize);

			if (expanded + size >= dstlen - 1)
				expanded = dstlen - size - 1;
			memcpy(dst + size, "        ", expanded);
			size += expanded;
		} else {
			dst[size++] = src[pos];
		}
	}

	dst[size] = 0;
}

struct enum_map {
	const char *name;
	int namelen;
	int value;
};

#define ENUM_MAP(name, value) { name, STRING_SIZE(name), value }

static bool
map_enum_do(struct enum_map *map, size_t map_size, int *value, const char *name)
{
	size_t namelen = strlen(name);
	int i;

	for (i = 0; i < map_size; i++)
		if (namelen == map[i].namelen &&
		    !string_enum_compare(name, map[i].name, namelen)) {
			*value = map[i].value;
			return TRUE;
		}

	return FALSE;
}

#define map_enum(attr, map, name) \
	map_enum_do(map, ARRAY_SIZE(map), attr, name)

static bool
io_read_buf(struct io *io, char buf[], size_t bufsize)
{
	bool error;

	io->buf = io->bufpos = buf;
	io->bufalloc = bufsize;
	error = !io_get(io, '\n', TRUE) && io_error(io);
	io->buf = NULL;

	return done_io(io) || error;
}

	return run_io_rd(&io, argv, FORMAT_NONE) && io_read_buf(&io, buf, bufsize);
}
static int
io_load(struct io *io, const char *separators,
	int (*read_property)(char *, size_t, char *, size_t))
{
	char *name;
	int state = OK;

	if (!start_io(io))
		return ERR;

	while (state == OK && (name = io_get(io, '\n', TRUE))) {
		char *value;
		size_t namelen;
		size_t valuelen;

		name = chomp_string(name);
		namelen = strcspn(name, separators);

		if (name[namelen]) {
			name[namelen] = 0;
			value = chomp_string(name + namelen + 1);
			valuelen = strlen(value);
		} else {
			value = "";
			valuelen = 0;
		}

		state = read_property(name, namelen, value, valuelen);
	}

	if (state != ERR && io_error(io))
		state = ERR;
	done_io(io);

	return state;
}

static int
run_io_load(const char **argv, const char *separators,
	    int (*read_property)(char *, size_t, char *, size_t))
{
	struct io io = {};

	return init_io_rd(&io, argv, NULL, FORMAT_NONE)
		? io_load(&io, separators, read_property) : ERR;
	REQ_(SCROLL_LEFT,	"Scroll two columns left"), \
	REQ_(SCROLL_RIGHT,	"Scroll two columns right"), \
LINE(AUTHOR,	   "author ",		COLOR_GREEN,	COLOR_DEFAULT,	0), \
LINE(MODE,         "",			COLOR_CYAN,	COLOR_DEFAULT,	0), \
LINE(TREE_HEAD,    "",			COLOR_DEFAULT,	COLOR_DEFAULT,	A_BOLD), \
	{ KEY_LEFT,	REQ_SCROLL_LEFT },
	{ KEY_RIGHT,	REQ_SCROLL_RIGHT },
static struct enum_map keymap_table[] = {
#define KEYMAP_(name) ENUM_MAP(#name, KEYMAP_##name)
#define set_keymap(map, name) map_enum(map, keymap_table, name)
static struct enum_map color_map[] = {
#define COLOR_MAP(name) ENUM_MAP(#name, COLOR_##name)
static struct enum_map attr_map[] = {
#define ATTR_MAP(name) ENUM_MAP(#name, A_##name)
#define set_color(color, name)		map_enum(color, color_map, name)
#define set_attribute(attr, name)	map_enum(attr, attr_map, name)
/* Wants: object fgcolor bgcolor [attribute] */
		static struct enum_map obsolete[] = {
			ENUM_MAP("main-delim",	LINE_DELIMITER),
			ENUM_MAP("main-date",	LINE_DATE),
			ENUM_MAP("main-author",	LINE_AUTHOR),
		};
		int index;
		if (!map_enum(&index, obsolete, argv[0])) {
		info = &line_info[index];
	if (!set_color(&info->fg, argv[1]) ||
	    !set_color(&info->bg, argv[2])) {
	if (argc == 4 && !set_attribute(&info->attr, argv[3])) {
static int parse_bool(bool *opt, const char *arg)
	*opt = (!strcmp(arg, "1") || !strcmp(arg, "true") || !strcmp(arg, "yes"))
		? TRUE : FALSE;
	return OK;
}

static int
parse_int(int *opt, const char *arg, int min, int max)
{
	int value = atoi(arg);

	if (min <= value && value <= max)
		*opt = value;
	return OK;
parse_string(char *opt, const char *arg, size_t optsize)
	int arglen = strlen(arg);
	switch (arg[0]) {
	case '\"':
	case '\'':
		if (arglen == 1 || arg[arglen - 1] != arg[0]) {
			config_msg = "Unmatched quotation";
			return ERR;
		}
		arg += 1; arglen -= 2;
	default:
		string_ncopy_do(opt, optsize, arg, strlen(arg));
		return OK;
	}
	if (!strcmp(argv[0], "show-author"))
		return parse_bool(&opt_author, argv[2]);
	if (!strcmp(argv[0], "show-date"))
		return parse_bool(&opt_date, argv[2]);
	if (!strcmp(argv[0], "show-rev-graph"))
		return parse_bool(&opt_rev_graph, argv[2]);
	if (!strcmp(argv[0], "show-refs"))
		return parse_bool(&opt_show_refs, argv[2]);
	if (!strcmp(argv[0], "show-line-numbers"))
		return parse_bool(&opt_line_number, argv[2]);
	if (!strcmp(argv[0], "line-graphics"))
		return parse_bool(&opt_line_graphics, argv[2]);
	if (!strcmp(argv[0], "line-number-interval"))
		return parse_int(&opt_num_interval, argv[2], 1, 1024);
	if (!strcmp(argv[0], "author-width"))
		return parse_int(&opt_author_cols, argv[2], 0, 1024);
	if (!strcmp(argv[0], "tab-size"))
		return parse_int(&opt_tab_size, argv[2], 1, 1024);
	if (!strcmp(argv[0], "commit-encoding"))
		return parse_string(opt_encoding, argv[2], sizeof(opt_encoding));
		static struct enum_map obsolete[] = {
			ENUM_MAP("cherry-pick",		REQ_NONE),
			ENUM_MAP("screen-resize",	REQ_NONE),
			ENUM_MAP("tree-parent",		REQ_PARENT),
		int alias;
		if (map_enum(&alias, obsolete, argv[2])) {
			if (alias != REQ_NONE)
				add_keybinding(keymap, alias, key);
		warn("Error on line %d, near '%.*s': %s",
		     config_lineno, (int) optlen, opt, config_msg);
	/* It's OK that the file doesn't exist. */
	if (io_load(&io, " \t", read_option) == ERR ||
		warn("Errors while loading %s.", path);
	if (!tigrc_system)
		tigrc_system = SYSCONFDIR "/tigrc";
	unsigned long yoffset;	/* Offset from the window side. */
	unsigned long p_yoffset;/* Previous offset from the window side */
	regex_t *regex;		/* Pre-compiled regexp */
	bool can_hscroll;	/* View can be scrolled horizontally. */
	/* Search for regexp in a line. */
	size_t skip = view->yoffset > view->col ? view->yoffset - view->col : 0;
		len = utf8_length(&string, skip, &col, max_len, &trimmed, use_tilde);
	if (len > 0)
		waddnstr(view->win, string, len);
	if (view->col + col >= view->width + view->yoffset)
		view->can_hscroll = TRUE;

	size_t skip = view->yoffset > view->col ? view->yoffset - view->col : 0;
	if (col < max && skip <= col) {
	col++;
	if (col < max && skip <= col)
		col = draw_space(view, LINE_DEFAULT, max - col, 1);
	view->col++;
	return view->width + view->yoffset <= view->col;
	view->col += draw_chars(view, type, string, view->width + view->yoffset - view->col, trim);
	size_t skip = view->yoffset > view->col ? view->yoffset - view->col : 0;
	for (i = skip; i < size; i++)
	if (size < max && skip <= size)
	view->col++;
	view->col += col;
	view->col += draw_space(view, LINE_DEFAULT, max - col, max - col);
	return view->width + view->yoffset <= view->col;
	return draw_field(view, LINE_AUTHOR, author, opt_author_cols, trim);
}

static bool
draw_mode(struct view *view, mode_t mode)
{
	static const char dir_mode[]	= "drwxr-xr-x";
	static const char link_mode[]	= "lrwxrwxrwx";
	static const char exe_mode[]	= "-rwxr-xr-x";
	static const char file_mode[]	= "-rw-r--r--";
	const char *str;

	if (S_ISDIR(mode))
		str = dir_mode;
	else if (S_ISLNK(mode))
		str = link_mode;
	else if (mode & S_IXUSR)
		str = exe_mode;
	else
		str = file_mode;

	return draw_field(view, LINE_MODE, str, sizeof(file_mode), FALSE);
	if (lineno == 0)
		view->can_hscroll = FALSE;

	case REQ_SCROLL_LEFT:
		if (view->yoffset == 0) {
			report("Cannot scroll beyond the first column");
			return;
		}
		if (view->yoffset <= SCROLL_INTERVAL)
			view->yoffset = 0;
		else
			view->yoffset -= SCROLL_INTERVAL;
		redraw_view_from(view, 0);
		report("");
		return;
	case REQ_SCROLL_RIGHT:
		if (!view->can_hscroll) {
			report("Cannot scroll beyond the last column");
			return;
		}
		view->yoffset += SCROLL_INTERVAL;
		redraw_view(view);
		report("");
		return;
	view->p_yoffset = view->yoffset;
	view->yoffset = 0;
	view->yoffset = view->p_yoffset;
	bool nomaximize = !!(flags & OPEN_REFRESH);
		current_view = 1;
		if (split) {
	case REQ_SCROLL_LEFT:
	case REQ_SCROLL_RIGHT:
static void
parse_timezone(time_t *time, const char *zone)
{
	long tz;

	tz  = ('0' - zone[1]) * 60 * 60 * 10;
	tz += ('0' - zone[2]) * 60 * 60;
	tz += ('0' - zone[3]) * 60;
	tz += ('0' - zone[4]);

	if (zone[0] == '-')
		tz = -tz;

	*time -= tz;
}

		if (zone && strlen(zone) == STRING_SIZE(" +0700"))
			parse_timezone(&time, zone + 1);
	char text[SIZEOF_STR];
	string_expand(text, sizeof(text), line->data, opt_tab_size);
	STRING_SIZE("100644 blob f931e1d229c3e185caad4449bf5b66ed72462657\t")
		if (!view->lines) {
			tree_entry(view, LINE_TREE_HEAD, opt_path, NULL, NULL);
			report("Tree is empty");
			return TRUE;
		}

	    !tree_entry(view, LINE_TREE_HEAD, opt_path, NULL, NULL))
	if (line->type == LINE_TREE_HEAD) {
		if (draw_mode(view, entry->mode))
		/* Depending on whether it is a subdirectory or parent link
		size_t linelen = string_expand_length(line, opt_tab_size);
		if (!blame)
			return FALSE;

		string_expand(blame->text, linelen + 1, line, opt_tab_size);
		parse_timezone(&author_time, line);
		struct status *file = unmerged;

		} else if (!file->status || file == unmerged) {
			/* Collapse all modified entries that follow an
			 * associated unmerged entry. */
			if (unmerged == file) {
				unmerged->status = 'U';
			} else if (file->status == 'U') {
				unmerged = file;
static void
status_update_onbranch(void)
{
	static const char *paths[][2] = {
		{ "rebase-apply/rebasing",	"Rebasing" },
		{ "rebase-apply/applying",	"Applying mailbox" },
		{ "rebase-apply/",		"Rebasing mailbox" },
		{ "rebase-merge/interactive",	"Interactive rebase" },
		{ "rebase-merge/",		"Rebase merge" },
		{ "MERGE_HEAD",			"Merging" },
		{ "BISECT_LOG",			"Bisecting" },
		{ "HEAD",			"On branch" },
	};
	char buf[SIZEOF_STR];
	struct stat stat;
	int i;

	if (is_initial_commit()) {
		string_copy(status_onbranch, "Initial commit");
		return;
	}

	for (i = 0; i < ARRAY_SIZE(paths); i++) {
		char *head = opt_head;

		if (!string_format(buf, "%s/%s", opt_git_dir, paths[i][0]) ||
		    lstat(buf, &stat) < 0)
			continue;

		if (!*opt_head) {
			struct io io = {};

			if (string_format(buf, "%s/rebase-merge/head-name", opt_git_dir) &&
			    io_open(&io, buf) &&
			    io_read_buf(&io, buf, sizeof(buf))) {
				head = chomp_string(buf);
				if (!prefixcmp(head, "refs/heads/"))
					head += STRING_SIZE("refs/heads/");
			}
		}

		if (!string_format(status_onbranch, "%s %s", paths[i][1], head))
			string_copy(status_onbranch, opt_head);
		return;
	}

	string_copy(status_onbranch, "Not currently on any branch");
}

	status_update_onbranch();
			text = "  (no files)";
		char mode[10] = "100644";
		const char *reset_argv[] = {
			"git", "update-index", "--cacheinfo", mode,
				status->old.rev, status->old.name, NULL
		};
		string_format(mode, "%o", status->old.mode);
		return (status->status != 'U' || run_io_fg(reset_argv, opt_cdup)) &&
			run_io_fg(checkout_argv, opt_cdup);
	open_view(view, REQ_VIEW_STATUS, OPEN_REFRESH);
		string_expand(commit->title, sizeof(commit->title), line, 1);
 * NOTE: Much of the following code for dealing with Unicode is derived from
 * src/intl/charset.c from the UTF-8 branch commit elinks-0.11.0-g31f2c28.
/* Decode UTF-8 multi-byte representation into a Unicode character. */
		die("Invalid Unicode length");
utf8_length(const char **start, size_t skip, int *width, size_t max_width, int *trimmed, bool reserve)
	const char *string = *start;
		/* FIXME: Graceful handling of invalid Unicode character. */
		if (skip > 0) {
			skip -= ucwidth <= skip ? ucwidth : skip;
			*start += bytes;
		}
		last_bytes = ucwidth ? bytes : 0;
	return string - *start;
	nonl();		/* Disable conversion and detect newlines from input. */
		/* it's an annotated tag, replace the previous SHA1 with the
	return run_io_load(ls_remote_argv, "\t", read_ref);
}

static void
set_repo_config_option(char *name, char *value, int (*cmd)(int, const char **))
{
	const char *argv[SIZEOF_ARG] = { name, "=" };
	int argc = 1 + (cmd == option_set_command);
	int error = ERR;

	if (!argv_from_string(argv, &argc, value))
		config_msg = "Too many option arguments";
	else
		error = cmd(argc, argv);

	if (error == ERR)
		warn("Option 'tig.%s': %s", name, config_msg);
	if (!prefixcmp(name, "tig.color."))
		set_repo_config_option(name + 10, value, option_color_command);

	else if (!prefixcmp(name, "tig.bind."))
		set_repo_config_option(name + 9, value, option_bind_command);

	else if (!prefixcmp(name, "tig."))
		set_repo_config_option(name + 4, value, option_set_command);

	return run_io_load(config_list_argv, "=", read_repo_config_option);
	return run_io_load(rev_parse_argv, "=", read_repo_info);
static const char usage[] =
"tig " TIG_VERSION " (" __DATE__ ")\n"
"\n"
"Usage: tig        [options] [revs] [--] [paths]\n"
"   or: tig show   [options] [revs] [--] [paths]\n"
"   or: tig blame  [rev] path\n"
"   or: tig status\n"
"   or: tig <      [git command output]\n"
"\n"
"Options:\n"
"  -v, --version   Show version and exit\n"
"  -h, --help      Show help message and exit";

static enum request
parse_options(int argc, const char *argv[])
{
	enum request request = REQ_VIEW_MAIN;
	const char *subcommand;
	bool seen_dashdash = FALSE;
	/* XXX: This is vulnerable to the user overriding options
	 * required for the main view parser. */
	const char *custom_argv[SIZEOF_ARG] = {
		"git", "log", "--no-color", "--pretty=raw", "--parents",
			"--topo-order", NULL
	};
	int i, j = 6;

	if (!isatty(STDIN_FILENO)) {
		io_open(&VIEW(REQ_VIEW_PAGER)->io, "");
		return REQ_VIEW_PAGER;
	}

	if (argc <= 1)
		return REQ_NONE;

	subcommand = argv[1];
	if (!strcmp(subcommand, "status")) {
		if (argc > 2)
			warn("ignoring arguments after `%s'", subcommand);
		return REQ_VIEW_STATUS;

	} else if (!strcmp(subcommand, "blame")) {
		if (argc <= 2 || argc > 4)
			die("invalid number of options to blame\n\n%s", usage);

		i = 2;
		if (argc == 4) {
			string_ncopy(opt_ref, argv[i], strlen(argv[i]));
			i++;
		}

		string_ncopy(opt_file, argv[i], strlen(argv[i]));
		return REQ_VIEW_BLAME;

	} else if (!strcmp(subcommand, "show")) {
		request = REQ_VIEW_DIFF;

	} else {
		subcommand = NULL;
	}

	if (subcommand) {
		custom_argv[1] = subcommand;
		j = 2;
	}

	for (i = 1 + !!subcommand; i < argc; i++) {
		const char *opt = argv[i];

		if (seen_dashdash || !strcmp(opt, "--")) {
			seen_dashdash = TRUE;

		} else if (!strcmp(opt, "-v") || !strcmp(opt, "--version")) {
			printf("tig version %s\n", TIG_VERSION);
			quit(0);

		} else if (!strcmp(opt, "-h") || !strcmp(opt, "--help")) {
			printf("%s\n", usage);
			quit(0);
		}

		custom_argv[j++] = opt;
		if (j >= ARRAY_SIZE(custom_argv))
			die("command too long");
	}

	if (!prepare_update(VIEW(request), custom_argv, NULL, FORMAT_NONE))                                                                        
		die("Failed to format arguments"); 

	return request;
}

	enum request request = parse_options(argc, argv);
	if (request != REQ_NONE)
	request = request == REQ_NONE ? REQ_VIEW_MAIN : REQ_NONE;
			else if (*opt_search)
				request = request == REQ_SEARCH ?
					REQ_FIND_NEXT :
					REQ_FIND_PREV;