typedef struct CSSSimpleSelector {
	// tag name
	char *tagName;
	// id
	char *idName;
	// class
	char *classes[20];
} CSSSimpleSelector;

typedef struct Declaration {
	char *name;
	union {
		char *keyword; // 关键字，如 position: 'fixed'
		struct Length; // 长度, width: 100px
		int color[4]; // rgba 颜色，rgba(255,255,255,0)
	};
} Declaration;

typedef struct Length {
	int value;
	enum unit {
		px=1,
		rem=2,
		em=3
	};
};