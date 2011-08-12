
SEO = {
	//! All terms
	terms: {},
	termNames: {},
	//! All articles
	articles: {},
	searchFromObjValue: function(root, index, id) {
		var o = document.getElementById(id);
		if (o)
			this.search(root, index, o.value);
	},
	search: function(root, index, query) {
		var div = document.getElementById('spotlight');
		if (!div)
			return;
		if (!query || query == "") {
			div.style.display = 'none';
			return;
		}
		var tks = query.split(new RegExp("[ ,;/|]", "g"));
		var tokens = new Array();
		var weight = 1.0;
		for (var i = 0; i < tks.length; ++i)
		{
			if (tks[i] == "")
				continue;
			var t = tks[i];
		
			if (t == "+")
				weight = 1.0;
			else if (t == "-")
				weight = -1.0;
			else {
				var cont = true;
				do {
					switch (t.charAt(0))
					{
						case '-': weight = 0;t = t.substring(1);break;
						case '+': weight = +1.0;t = t.substring(1);break;
						default:cont = false;
					}
				} while (cont);

				var tid = SEO.termNames[t];
				if (!tid || tid <= 0)
					continue;
				var r = {
					id: tid,
					term: t,
					w: weight + 0.5 * (i / tks.length),//* ((tks.length - i) / tks.length),
					pages: SEO.terms[tid]
				};
				// updating weights
				for (var j = 0; j != r.pages.length; ++j)
					r.pages[j].w *= r.w;
				tokens.push(r);
			}
		}

		var pages = {};
		for (var i = 0; i != tokens.length; ++i) {
			var r = tokens[i];
			for (var j = 0; j != r.pages.length; ++j) {
				var articleid = r.pages[j].a;
				if (!pages[articleid]) {
					pages[articleid] = {
						a: articleid,
						w: r.pages[j].w,
					};
				} else {
					if (r.w > 0)
						pages[articleid].w *= 1.3;
					else
						pages[articleid].w = 0;
				}
			}
		}
		var result = [];
		for (var i in pages) {
			var p = pages[i];
			if (p.w > 0.05)
				result.push({id: p.a, w: p.w});
		}
		div.style.display = 'block';
		if (result.length) {
			result.sort(function(a,b) {
				if (a.w < b.w)
					return 1;
				if (a.w > b.w)
					return -1;
				return 0;
			});
			var s = '<span>research</span>';
			for (var t in tokens) {
				var tok = tokens[t];
				s += " " + tok.term;
			}
			s += "<br />";
			for (var i in result) {
				var r = result[i];
				s += "<a href=\"" + root + SEO.articles[r.id].h  + "/" + index + "\">"
					+ "<span>" + SEO.articles[r.id].t + "</span>  "
					+ SEO.articles[r.id].h + "</a>";
			}
			div.innerHTML = s;
		}
		else
			div.innerHTML = "<a href='#'><span>No result</span></a>";
	}

};
