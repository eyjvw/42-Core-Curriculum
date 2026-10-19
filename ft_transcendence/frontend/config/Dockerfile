FROM oven/bun:1.1 AS build

WORKDIR /app

COPY frontend/config/package.json frontend/config/bun.lock ./
RUN bun install

COPY frontend/config/vite.config.ts frontend/config/tsconfig.json frontend/config/tsconfig.app.json frontend/config/tsconfig.node.json frontend/config/eslint.config.js ./
COPY frontend/index.html ./
COPY frontend/src ./src
COPY frontend/public ./public

RUN bun run build

FROM nginx:alpine

COPY frontend/config/nginx.conf /etc/nginx/conf.d/default.conf
COPY --from=build /app/dist /usr/share/nginx/html

EXPOSE 3000
