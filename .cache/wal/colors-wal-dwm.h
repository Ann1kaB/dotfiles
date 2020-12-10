static const char norm_fg[] = "#f6ddec";
static const char norm_bg[] = "#642e45";
static const char norm_border[] = "#ac9aa5";

static const char sel_fg[] = "#f6ddec";
static const char sel_bg[] = "#FFBECD";
static const char sel_border[] = "#f6ddec";

static const char urg_fg[] = "#f6ddec";
static const char urg_bg[] = "#D5A3D2";
static const char urg_border[] = "#D5A3D2";

static const char *colors[][3]      = {
    /*               fg           bg         border                         */
    [SchemeNorm] = { norm_fg,     norm_bg,   norm_border }, // unfocused wins
    [SchemeSel]  = { sel_fg,      sel_bg,    sel_border },  // the focused win
    [SchemeUrg] =  { urg_fg,      urg_bg,    urg_border },
};
