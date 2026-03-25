FROM oven/bun:1.1

WORKDIR /app

COPY backend/social/config/package.json backend/social/config/bun.lock ./
RUN bun install

COPY backend/social/src ./src
COPY backend/db ./db

RUN mkdir -p /app/data

EXPOSE 4001

CMD ["bun", "run", "src/index.ts"]
