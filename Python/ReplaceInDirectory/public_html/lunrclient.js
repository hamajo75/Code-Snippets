"use strict";

var LUNR_CONFIG = {
    "resultsElementId": "searchResults",  // Element to contain results
    "countElementId": "resultCount"  // Element showing number of results
};


// Get URL arguments
function getParameterByName(name, url) {
    if (!url) url = window.location.href;
    name = name.replace(/[\[\]]/g, "\\$&");
    var regex = new RegExp("[?&]" + name + "(=([^&#]*)|&|#|$)"),
        results = regex.exec(url);
    if (!results) return null;
    if (!results[2]) return "";
    return decodeURIComponent(results[2].replace(/\+/g, " "));
}


// Parse search results into HTML
function parseLunrResults(results) {
    var html = [];
    var current_title = "";
    var result = "";
    results.sort(function(a, b){
        var item_a = PREVIEW_LOOKUP[a["ref"]];
        var item_b = PREVIEW_LOOKUP[b["ref"]];
        var title_a = item_a["t"];
        var title_b = item_b["t"];

        if(title_a < title_b) {return -1;}
        if(title_a > title_b) {return 1;}
        return 0;
    })
    for (var i = 0; i < results.length; i++) {
        var id = results[i]["ref"];
        var item = PREVIEW_LOOKUP[id]
        var title = item["t"];
        var preview = item["p"];
        var link = item["l"];

        if (title != current_title){
            current_title = title;    
            if (i > 0)
                html.push(result);
            
            result = "/* new title */\n";                
            result = ('<span class="result-title"><p>'+ title +'</p></span>') + '\n' + 
                     ('<span class="result-preview"><p><a href="' + link + '">'
                        + preview + '</a></p></span>');
        }
        else{
            result = result + '\n' + ('<span class="result-preview"><p><a href="' + link + '">'
                        + preview + '</a></p></span>');
        }        
    }
    html.push(result);  // last result
    html.push("<p><br></p>");
    if (html.length) {
        return html.join("");
    }
    else {
        return "<p>Your search returned no results.</p>";
    }
}


function escapeHtml(unsafe) {
    return unsafe
         .replace(/&/g, "&amp;")
         .replace(/</g, "&lt;")
         .replace(/>/g, "&gt;")
         .replace(/"/g, "&quot;")
         .replace(/'/g, "&#039;");
}


function showResultCount(query, total, domElementId) {
    if (total == 0) {
        return;
    }

    var s = "";
    if (total > 1) {
        s = "s";
    }
    var found = "<p>Found " + total + " result" + s;
    if (query != "" && query != null) {
        query = escapeHtml(query);
        var forQuery = ' for <span class="result-query"><mark>' + query + '</mark></span>';
    }
    else {
        var forQuery = "";
    }
    var element = document.getElementById(domElementId);
    element.innerHTML = found + forQuery + "</p>";
}

function highlightSearchResults(resultHtml, query){

    var query_split = query.split(" ");
    var last_word = "";
    query_split.forEach(function(word)
    {
        if (word != last_word)
        {
            resultHtml = resultHtml.replace(new RegExp(word, "gi"), (match) => `<mark>${match}</mark>`);       // highlight results
            //resultHtml = resultHtml.replace(new RegExp("(" + query + ")", "gi"), "<mark>$1</mark>");            
        }
        last_word = word;
    });
    return resultHtml;
}

function searchLunr(query) {
    var idx = lunr.Index.load(LUNR_DATA);   // LUNR_DATA is the name of the variable in lunr_index.js
    // Write results to page
    var results = idx.search(query);
    var resultHtml = parseLunrResults(results, query);
    var elementId = LUNR_CONFIG["resultsElementId"];
    document.getElementById(elementId).innerHTML = highlightSearchResults(resultHtml, query);

    var count = results.length;
    showResultCount(query, count, LUNR_CONFIG["countElementId"]);
}


// When the window loads, read query parameters and perform search
window.onload = function() {
    var query = getParameterByName("q");
    
    if (query != "" && query != null) {
        document.forms.lunrSearchForm.q.value = query;
        searchLunr(query);
    }
};