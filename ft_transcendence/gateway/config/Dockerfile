FROM oven/bun:1.1

WORKDIR /app

COPY gateway/config/package.json gateway/config/bun.lock* ./
RUN bun install

COPY gateway/src ./src

EXPOSE 8000

CMD ["bun", "run", "src/index.ts"]