#!/bin/bash
set -e

# Git補完機能をインストール
curl -o /usr/share/bash-completion/completions/git-completion.bash \
    https://raw.githubusercontent.com/git/git/master/contrib/completion/git-completion.bash
curl -o /usr/share/bash-completion/completions/git-prompt.sh \
    https://raw.githubusercontent.com/git/git/master/contrib/completion/git-prompt.sh
chmod 755 /usr/share/bash-completion/completions/git-*.bash
chmod 755 /usr/share/bash-completion/completions/git-*.sh

# doctestをグローバルに配置
mkdir -p /usr/local/include/doctest
cp /tmp/doctest/doctest.h /usr/local/include/doctest/
chmod 644 /usr/local/include/doctest/doctest.h

# 開発環境設定スクリプトを配置
cp /tmp/omusubi-dev.sh /etc/profile.d/omusubi-dev.sh
chmod 644 /etc/profile.d/omusubi-dev.sh

# 非ログインシェルでも読み込まれるように設定
cat >> /etc/bash.bashrc <<'EOF'

# Omusubi開発環境設定を読み込み
[ -f /etc/profile.d/omusubi-dev.sh ] && source /etc/profile.d/omusubi-dev.sh
EOF
