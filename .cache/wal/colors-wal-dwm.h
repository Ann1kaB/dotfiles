static const char norm_fg[] = "#a7b8e9";
static const char norm_bg[] = "#000113";
static const char norm_border[] = "#7480a3";

static const char sel_fg[] = "#a7b8e9";
static const char sel_bg[] = "#070492";
static const char sel_border[] = "#a7b8e9";

static const char urg_fg[] = "#a7b8e9";
static const char urg_bg[] = "#B40463";
static const char urg_border[] = "#B40463";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
    [SchemeUrg] =  { urg_fg,      urg_bg,    urg_border },
};
