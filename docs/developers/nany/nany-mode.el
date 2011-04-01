;; Emacs major mode for Nany language. Written by the Yuni project team.
;; Free to use, redistribute, and modify freely.
;;
;; You may add the following to your init.el :
;; (autoload 'nany-mode "/path/to/nany-mode.el" "Major mode for editing Nany source code." t)
;; (setq auto-mode-alist (append '(("\\.nany$" . nany-mode)) auto-mode-alist))


(defgroup nany nil
  "Major mode for editing Nany source code."
  :link '(custom-group-link :tag "Font Lock Faces group" font-lock-faces)
  :prefix "nany-"
  :group 'languages
)

(defvar nany-mode-hook nil)

;;;###autoload
(add-to-list 'auto-mode-alist '("\\.nany\\'" . nany-mode))

(defvar nany-mode-abbrev-table nil
  "Abbrev table in use in nany-mode buffers.")
(define-abbrev-table 'nany-mode-abbrev-table ())

;; Syntax table
(defvar nany-mode-syntax-table
  (let ((table (make-syntax-table)))
    (modify-syntax-entry ?\( "()" table)
    (modify-syntax-entry ?\) ")(" table)
    (modify-syntax-entry ?\[ "(]" table)
    (modify-syntax-entry ?\] ")[" table)
    (modify-syntax-entry ?\{ "(}" table)
    (modify-syntax-entry ?\} "){" table)
    (modify-syntax-entry ?# "<" table)
    (modify-syntax-entry ?\n ">" table)
    (modify-syntax-entry ?' "\"" table)
    (modify-syntax-entry ?` "$" table)
    table
  )
)


;; Keywords
(defvar nany-keywords
  '("and" "as" "async" "catch" "check" "class" "clone" "const" "distributed" "every" "for" "foreach" "function" "if" "in" "immutable" "is" "method" "new" "not" "notify" "operator" "on" "or" "persistent" "predicate" "property" "read" "ref" "return" "self" "shared" "stable" "sync" "threadunsafe" "type" "typeof" "variadic" "while" "write" "xor")
  "Nany keywords")
;; Regexped version
(defvar nany-keywords-regexp (regexp-opt nany-keywords 'words))

;; File-level keywords
(defvar nany-file-keywords
  '("program" "unit" "library" "uses" "implementation")
  "Nany file-level keywords")
;; Regexped version
(defvar nany-file-keywords-regexp (regexp-opt nany-file-keywords 'words))

;; Built-in Types
(defvar nany-builtin-types
  '("int" "int8" "int16" "int32" "int64" "uint" "uint8" "uint16" "uint32" "uint64" "char" "bool" "float" "double" "string" "any")
  "Nany builtin types")
;; Regexped version
(defvar nany-builtin-types-regexp (regexp-opt nany-builtin-types 'words))

;; Built-in Types
(defvar nany-operators
  '(":" "\\=\\>" "\\>" "\\-\\>" "\\<" "\\<=" ":\\=" "\\=" "\\>\\=")
  "Nany operators")
;; Regexped version
(defvar nany-operators-regexp (regexp-opt nany-operators 'words))

;; Constants
(defvar nany-constants
  '("true" "false" "nil")
  "Nany constants")
;; Regexped version
(defvar nany-constants-regexp (regexp-opt nany-constants 'words))


;; Syntax highlighting
(defconst nany-font-lock-keywords-1
  (list
	'(,(nany-file-keywords-regexp) font-lock-preprocessor-face)
    ;; Method prototype
;    '("^[ \t]*\\(const\\|stable\\|immutable\\)?[ \t]+\\(threadunsafe\\)?[ \t]+\\(method\\|function\\)\\>[ \t]*\\([A-Za-z][A-Za-z0-9_]*\\)"
;     (1 font-lock-keyword-face) (5 font-lock-function-name-face))
	;; Function calls
;	'("\\.*\\([A-Za-z][A-Za-z0-9_]*\\)[ \t]*(" 1 font-lock-function-name-face)
  )
  "Level-1 (subdued) syntax highlighting in Nany mode"
)

(defconst nany-font-lock-keywords-2
  (append nany-font-lock-keywords-1
    (list
      '(,nany-keywords-regexp . font-lock-keyword-face)
;      '(,nany-builtin-types-regexp . font-lock-type-face)
;;      '(,nany-operators-regexp . font-lock-symbol-face)
;      '(,nany-constants-regexp . font-lock-constant-face)
	  ;; Do these in the end
;	  '("[A-Za-z][A-Za-z0-9_]*" . font-lock-variable-name-face)
;      '("[0-9]+" . font-lock-constant-face)
     )
  )
  "Level-2 (gaudy) syntax highlighting in Nany mode"
)

(defvar nany-font-lock-keywords nany-font-lock-keywords-2
  "Default expressions to highlight in Nany mode.")

(defcustom nany-indent-level 4
  "*Indentation of Nany statements with respect to containing block."
  :type 'integer
  :group 'nany)



;; Command to comment/uncomment text
(defun nany-comment-dwim (arg)
  "Comment or uncomment current line or region in a smart way.
  For detail, see `comment-dwim'."
  (interactive "*P")
  (require 'newcomment)
  (let ((deactivate-mark nil) (comment-start "#") (comment-end ""))
    (comment-dwim arg)
  )
)

;; Command to indent a line
(defun nany-indent-line ()
  "Indent current line as Nany code"
  (interactive)
  (beginning-of-line)
  ; Beginning of buffer
  (if (bobp)
    (indent-line-to 0)
  (let ((not-indented t) cur-indent)
  ; End of scope, indent -1
  (if (looking-at "^[ \t]*}")
    (progn
      (save-excursion
        (forward-line -1)
		(if (looking-at "^[ \t]*{")
          ()
          (setq cur-indent (- (current-indentation) default-tab-width))
        )
      )
      (if (< cur-indent 0)
        (setq cur-indent 0)
      )
    )
    ; Find an indentation hint from above the current line
    (save-excursion
      (while not-indented
        (forward-line -1)
        ; If we found an end of scope, use its indent level
        (if (looking-at "^[ \t]*}")
          (progn
            (setq cur-indent (current-indentation))
            (setq not-indented nil)
          )
  		; If we found a beginning of scope, increase indent level from this one
          (if (looking-at "^[ \t]*{")
            (progn
              (setq cur-indent (+ (current-indentation) default-tab-width))
                (setq not-indented nil)
            )
  		  ; Default
            (if (bobp)
              (setq not-indented nil)
            )
          )
        )
      )
    )
  )
  ; Do the actual indentation if we found an indentation hint
  (if cur-indent
    (indent-line-to cur-indent)
    (indent-line-to 0))
  )
  )
)



;; Command for keyword completion
(defun nany-complete-symbol ()
  "Perform keyword completion on word before cursor."
  (interactive)
  (let ((posEnd (point))
         (meat (thing-at-point 'symbol))
         maxMatchResult
       )

    ;; When nil, set it to empty string, so user can see all lang's keywords.
    ;; If not done, try-completion on nil result lisp error.
    (when (not meat) (setq meat ""))
    (setq maxMatchResult (try-completion meat nany-keywords))

    (cond ((eq maxMatchResult t))
      ((null maxMatchResult)
        (message "Can't find completion for “%s”" meat) (ding)
      )
      ((not (string= meat maxMatchResult))
        (delete-region (- posEnd (length meat)) posEnd)
        (insert maxMatchResult)
      )
      (t (message "Making completion list...")
        (with-output-to-temp-buffer "*Completions*"
          (display-completion-list
            (all-completions meat nany-keywords)
            meat)
          )
          (message "Making completion list...%s" "done")
      )
    )
  )
)

;; Set keymap
(defvar nany-mode-map
  (let ((map (make-keymap)))
    (define-key map "\C-j" 'newline-and-indent)
    (define-key map [remap comment-dwim] 'nany-comment-dwim)
    (define-key map (kbd "C-c C-c") 'comment-region)
    (define-key map (kbd "C-c c") 'nany-complete-symbol)
    map
  )
  "Keymap for Nany major mode"
)

;; Define the major mode
(defun nany-mode ()
  "Major mode for editing Nany code. You may use nany-indent-line, nany-complete-symbol, nany-comment-dwim."
  (interactive)
  (kill-all-local-variables)
  ;; Key mappings
  (use-local-map nany-mode-map)
  ;; Major mode definition
  (setq major-mode 'nany-mode)
  ;; Mode name
  (setq mode-name "Nany")
  ;; Abbrev table
  (setq local-abbrev-table nany-mode-abbrev-table)
  (message nany-keywords-regexp)
  ;; Syntax table
  (set-syntax-table nany-mode-syntax-table)
  ;; Comments
  (set (make-local-variable 'comment-start) "#")
  (set (make-local-variable 'comment-end) "")
  ;; Use tab indents
  (set (make-local-variable 'indent-tabs-mode) t)
  ;; Font lock
  (set (make-local-variable 'font-lock-defaults) '(nany-font-lock-keywords))
  ;; Indentation
  (set (make-local-variable 'indent-line-function) 'nany-indent-line)
  (provide 'nany-mode)
)
