FROM oven/bun:1.1

WORKDIR /app

COPY frontend/config/package.json frontend/config/bun.lock ./
RUN bun install

COPY frontend/config/vite.config.ts frontend/config/tsconfig.json frontend/config/tsconfig.app.json frontend/config/tsconfig.node.json frontend/config/eslint.config.js ./
COPY frontend/index.html ./
COPY frontend/src ./src
COPY frontend/public ./public

EXPOSE 3000

CMD ["bun", "run", "dev"]
